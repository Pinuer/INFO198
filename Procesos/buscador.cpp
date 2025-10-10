#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <tuple>
#include <algorithm> 
#include "common.h"
#include "file_operation.h"
#include "func_string.h"

using namespace std;

// Conecta al servidor
int connectServer(const string& serverIP, int serverPort) {
    cout << "IP :" << serverIP << endl;
    cout << "PUERTO: " << serverPort << endl;
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("BUSC:Error al crear el socket del cliente");
        exit(EXIT_FAILURE);
    }
    cout << "BUSC:socket creado" << endl;

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("BUSC: Error al conectar al servidor");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
    cout << "BUSC:Conectado al servidor." << endl;

    return clientSocket;
}

// Envía mensaje al servidor
void sendMessage(int clientSocket, const string& message) {
    cout << "BUSC:Enviando mensaje al servidor..." << endl;
    send(clientSocket, message.c_str(), message.length(), 0);
}

// Recibe mensaje del servidor
string recieveMessage(int clientSocket) {
    char buffer[1024];
    string respuesta;
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("BUSC:Error al recibir datos del servidor");
        close(clientSocket);
        exit(EXIT_FAILURE);
    } else if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        respuesta = buffer;
    }
    return respuesta;
}

int main() {
    int PORT = std::stoi(getenv("CACHE_PORT"));
    const char* IP_SERVER = getenv("IP_SERVER"); 

    bool keepSearching = true;
    string search;
    string searchNormal;
    vector<string> splitedSearch = {};
    vector<string> recievedSearch = {};
    vector<string> mapa = read_file(getenv("MAPA_ARCHIVOS"));
    string recievedMessage = "";
    vector<tuple<int, int>> addVector = {};
    vector<string> tempTuple = {};

    cout << "PID PROCESO: " << getpid() << endl;
    cout << "Iniciando Buscador" << endl << endl;
    cout << "Conectando al servidor" << endl;
    int cacheSocket = connectServer(IP_SERVER, PORT);
    sleep(1);

    do {
        cout << "Ingrese búsqueda(o salir ahora para finalizar): ";
        getline(cin, search);

        // Normalizar la entrada
        for (char c : search) {
            searchNormal += tolower(c);
        }

        if (searchNormal == "salir ahora") {
            cout << "SALIENDO..." << endl;
            sendMessage(cacheSocket, "salir_ahora");
            keepSearching = false;
            sleep(1);
        } else {
            cout << "BUSQ: enviando a cache: " << searchNormal << endl;
            sendMessage(cacheSocket, searchNormal);

            do {
                recievedMessage = recieveMessage(cacheSocket);
                cout << "BUSQ: mensaje recibido: " << recievedMessage << endl;
                if (recievedMessage != "check") recievedSearch.push_back(recievedMessage);
            } while (recievedMessage != "check");

            print_separation();

            // Concatenar las palabras clave de la búsqueda y mostrar antes de los resultados
            string keywords;
            for (const string& line : recievedSearch) {
                splitedSearch = split(line, ";");
                keywords += splitedSearch[0] + " ";  // Agrega cada palabra a la lista de palabras clave
            }
            cout << "Palabras clave: " << keywords << endl;

            // Procesar y mostrar cada palabra y sus resultados
            for (const string& line : recievedSearch) {
                splitedSearch = split(line, ";");
                cout << splitedSearch[0] << ": ";

                if (splitedSearch[1] != "No Se encontro") {
                    for (size_t j = 1; j < splitedSearch.size(); j++) {
                        splitedSearch[j] = remove_character(splitedSearch[j], '(');
                        splitedSearch[j] = remove_character(splitedSearch[j], ')');
                        cout << splitedSearch[j] << " | ";
                        tempTuple = split(splitedSearch[j], ",");

                        // Verificación de valores válidos en tempTuple
                        if (tempTuple.size() < 2 || tempTuple[0].empty() || tempTuple[1].empty()) {
                            cerr << "Error: entrada inválida: " << splitedSearch[j] << endl;
                            continue;
                        }

                        try {
                            int idLibro = stoi(tempTuple[0]);
                            int puntaje = stoi(tempTuple[1]);

                            auto it = find_if(addVector.begin(), addVector.end(), 
                                              [&idLibro](const tuple<int, int>& t) {
                                                  return get<0>(t) == idLibro;
                                              });
                            if (it != addVector.end()) {
                                get<1>(*it) += puntaje;
                            } else {
                                addVector.push_back({idLibro, puntaje});
                            }
                        } catch (const invalid_argument& e) {
                            cerr << "Error de conversión a entero en: " << tempTuple[0] << ", " << tempTuple[1] << endl;
                            continue;
                        }
                    }
                    cout << endl;
                }
            }

            // Ordena addVector de mayor a menor por el puntaje 
            sort(addVector.begin(), addVector.end(), [](const tuple<int, int>& a, const tuple<int, int>& b) {
                return get<1>(a) > get<1>(b);
            });
            
            // Eliminar la limitación de topk
            for (const auto& result : addVector) {
                cout << "ID libro: " << get<0>(result) << " Puntaje: " << get<1>(result) << endl;
            }
        }

        searchNormal = "";
        addVector.clear();
        recievedSearch.clear();

    } while (keepSearching);

    return 0;
}
