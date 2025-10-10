#ifndef FUNC_PLANIFICADOR_H
#define FUNC_PLANIFICADOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int obtener_core_disponible();     // Función para obtener el primer core disponible
void liberar_core(int core_id);    // Función para liberar el core
void ejecutar();                   // Función principal para ejecutar el planificador

#endif 
