#ifndef THREAD_OPERATION_H
#define THREAD_OPERATION_H

#include <string>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <mutex>
using namespace std;


void cargarStopWords(string archivoStopWords);
map<string, int> contarPalabras(string filename);
void actualizarConteoGlobal(map<string, int> &conteoPalabras, int id);
void *print_file_path(void *threadOperation);
void open_threads();
void crearMapaArchivo();

#endif 
