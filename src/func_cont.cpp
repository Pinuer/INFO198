#include "func_cont.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <cctype>

//Cuenta el n° de veces que se repite cada palabra en un archivo
map<string, int> contarPalabras(string &filename) {
    map<string, int> cont;
    ifstream archivo(filename); 

    if (!archivo.is_open()) {
        cerr<<"No se puede abrir el archivo: "<<filename<< endl;
        return cont;
    }

    string palabra;
    while (archivo >> palabra) {
        for (char c : palabra) {
            c = tolower(c);        
        }
        cont[palabra]++;
    }

    archivo.close();
    return cont;
}

//Procesa todos los archivos con una extensión ingresada
void procesarArchivos(string ext, string entrada, string salida) {
    bool archivosEncontrados = false;

    for (auto& ent : std::filesystem::directory_iterator(entrada)) {
        if (ent.path().extension() == "." + ext) {
            archivosEncontrados = true;
            string archivoEntrada = ent.path().string();
            map<string, int> conteoPalabras = contarPalabras(archivoEntrada);
            string archivoSalida = salida + "/" + ent.path().filename().string();
            ofstream outFile(archivoSalida);

            for (auto& [palabra, cantidad] : conteoPalabras) {
                outFile<<palabra<<": "<<cantidad<<endl;
            }

            outFile.close();
            cout<<"Archivo: "<<archivoSalida<<", "<<conteoPalabras.size()<<" palabras distintas"<<endl;
        }
    }

    if (!archivosEncontrados) {
        cout<<"No se encontraron archivos con la extensión especificada en la carpeta de entrada"<<endl;
    }
}
