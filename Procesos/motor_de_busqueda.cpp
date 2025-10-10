#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

#include "common.h"
#include "file_operation.h"
#include "func_string.h"

using namespace std;

// Estructura para almacenar el índice invertido en memoria
map<string, vector<pair<int, int>>> invertedIndex;

void loadInvertedIndex() {
    ifstream file(getenv("INVERTED_INDEX"));
    string line;

    while (getline(file, line)) {
        vector<string> splitedLine = split(line, ";");
        string word = splitedLine[0];

        vector<pair<int, int>> entries;
        for (size_t i = 1; i < splitedLine.size(); i++) {
            string entry = remove_character(splitedLine[i], '(');
            entry = remove_character(entry, ')');
            vector<string> tempTuple = split(entry, ",");

            if (tempTuple.size() == 2) {
                try {
                    int idLibro = stoi(tempTuple[0]);
                    int puntaje = stoi(tempTuple[1]);
                    entries.emplace_back(idLibro, puntaje);
                } catch (const invalid_argument&) {
                    cerr << "Error de conversión en línea: " << line << endl;
                }
            }
        }
        invertedIndex[word] = entries;
    }
    file.close();
}

vector<pair<int, int>> searchWord(const string& search) {
    int TOPK = stoi(getenv("TOPK"));
    if (invertedIndex.find(search) == invertedIndex.end()) {
        return {};
    }

    // Obtener libros asociados a la palabra y calcular puntajes
    map<int, int> scores;
    for (const auto& entry : invertedIndex[search]) {
        int idLibro = entry.first;
        int puntaje = entry.second;
        scores[idLibro] += puntaje;
    }

    // Convertir a vector de pares y ordenar
    vector<pair<int, int>> result(scores.begin(), scores.end());
    sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;  // Orden descendente de puntajes
    });

    // Limitar al valor de TOPK
    if (result.size() > TOPK) {
        result.resize(TOPK);
    }
    return result;
}

// Procesar la solicitud y devolver el resultado en el formato esperado
string processSearchRequest(const string& search) {
    vector<pair<int, int>> results = searchWord(search);
    if (results.empty()) {
        return search + ";No Se encontro";
    }

    string response = search + ";";
    for (const auto& [idLibro, puntaje] : results) {
        response += "(" + to_string(idLibro) + "," + to_string(puntaje) + ");";
    }
    response.pop_back();  // Eliminar el último ';'
    return response;
}

// Función para manejar cada cliente entrante
void handleClient(int clientSocket, bool& serverRunning) {
    char buffer[1024];
    ssize_t bytesRead;
    string respuesta;
    bool continua = true;

    while (continua) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) break;  // Fin de la conexión
        buffer[bytesRead] = '\0';
        respuesta = buffer;

        if (respuesta == "salir_ahora") {
            continua = false;
            serverRunning = false;  // Señala que el servidor debe cerrar
            cout << "MOTOR: Saliendo..." << endl;
        } else {
            string result = processSearchRequest(respuesta);
            cout << "MOTOR: Enviando resultado a cache: " << result << endl;
            send(clientSocket, result.c_str(), result.length(), 0);
        }
    }

    close(clientSocket);  // Cerrar el socket del cliente
    cout << "Motor Stop " << endl;
    exit(0);
}

int main() {
    loadInvertedIndex();  // Cargar el índice invertido al iniciar

    const int opt = 1;
    int PORT_MOTOR = std::stoi(getenv("MOTOR_PORT"));
    cout << "MOTOR: PORT: " << PORT_MOTOR << endl;
    cout << "MOTOR: PID: " << getpid() << endl;

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    bool serverRunning = true;

    // Crear socket del servidor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (serverSocket == -1) {
        perror("MOTOR: Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }

    // Configurar dirección del servidor
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_MOTOR);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Enlazar el socket a la dirección del servidor
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("MOTOR: Error al enlazar el socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, 5) == -1) {
        perror("MOTOR: Error al escuchar");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    cout << "MOTOR: Esperando conexiones entrantes..." << endl;

    // Aceptar y manejar conexiones
    while (serverRunning) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            if (!serverRunning) break;  // Si el servidor ya no está activo, salir
            perror("MOTOR: Error al aceptar la conexión");
            continue;
        }
        cout << "MOTOR: Cliente conectado" << endl;

        thread(handleClient, clientSocket, ref(serverRunning)).detach();
    }

    close(serverSocket);  // Cerrar el socket del servidor al salir
    cout << "MOTOR: Servidor cerrado" << endl;

    return 0;
}
