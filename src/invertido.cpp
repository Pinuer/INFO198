#include "invertido.h"
#include "func_string.h"

map<string, map<int, int>> invertedIndex;

void cargarConteo(string& outputDir, string& extension) {
    for (auto& ent : filesystem::directory_iterator(outputDir)) {
        if (ent.path().extension() == "." + extension) {
            int fileID = stoi(ent.path().stem().string()); // Asume que el nombre del archivo es el ID
            ifstream archivo(ent.path());
            string palabra;
            int cantidad;

            while (archivo >> palabra >> cantidad) {
                palabra = remove_character(palabra,';');
                palabra = remove_character(palabra,' ');
                invertedIndex[palabra][fileID] += cantidad; // Acumula el conteo de la palabra
            }
            archivo.close();
        }
    }
}

void crearIndiceInvertido(string& outputFilePath) {
    ofstream output(outputFilePath);
    if (!output.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir el índice invertido: " << outputFilePath << endl;
        return;
    }

    // Escribir el índice invertido en el archivo de salida
    for (auto& word : invertedIndex) {
        output << word.first; // La palabra
        for (auto& [id, cantidad] : word.second) {
            output << ";(" << id << "," << cantidad << ")"; // (ID, Cantidad)
        }
        output << endl;
    }

    output.close();
    cout << "Índice invertido creado exitosamente en: " << outputFilePath << endl;
}
