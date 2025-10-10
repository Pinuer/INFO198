#include "func_core.h"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        // Recibir core_id como primer argumento
        int core_id = stoi(argv[1]);
        string operacion = argv[2];
        
        calcular(core_id, operacion);
    }
    return 0;
}
