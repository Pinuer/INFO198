#include "func_distribuidor.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        string mensaje = argv[1];
        procesar_mensaje(mensaje);
    }
    return 0;
}
