#ifndef INVERTIDO_H
#define INVERTIDO_H

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <filesystem>

using namespace std;


void cargarConteo(string& outputDir, string& extension);
void crearIndiceInvertido(string& outputFilePath);

#endif 
