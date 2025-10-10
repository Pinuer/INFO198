#ifndef FUNC_CONT_H
#define FUNC_CONT_H

#include <map>
#include <string>

using namespace std;

map<string, int> contarPalabras(string &filename);
void procesarArchivos(string ext, string entrada, string salida);

#endif