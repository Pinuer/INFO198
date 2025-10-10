#include <iostream>
#include "thread_operation.h"
#include "env_setter.h"

using namespace std;

int main(int argc, char** argv) {
    cout<<"PID: "<<getpid()<<endl;
    string archivoStopWords = get_enviroment_variable("STOP_WORDS");
    cargarStopWords(archivoStopWords);
    open_threads();
    crearMapaArchivo(); 
}


