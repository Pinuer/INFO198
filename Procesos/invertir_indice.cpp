#include <iostream>
#include "invertido.h"
#include "env_setter.h"

using namespace std;

int main(int argc, char** argv) {
    cout<<"PID: "<<getpid()<<endl;
    string outputDir = get_enviroment_variable("OUTPUT_DIR");
    string extension = get_enviroment_variable("EXTENSION");
    string invertedIndexPath = get_enviroment_variable("INVERTED_INDEX");

    cargarConteo(outputDir, extension);
    crearIndiceInvertido(invertedIndexPath);
}
