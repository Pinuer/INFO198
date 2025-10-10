#include "func_distribuidor.h"

void procesar_mensaje(string& mensaje) {
    int core_id;
    string operacion;

    // Parsear mensaje
    size_t pos = mensaje.find(":");
    if (pos != string::npos) {
        core_id = stoi(mensaje.substr(0, pos)); // Extraer core_id
        operacion = mensaje.substr(pos + 1);    // Extraer operación
    }
    cout<<core_id<<": "<<operacion<<endl; // Salida de depuración
    // Convertir core_id a string
    string core_id_str = to_string(core_id);

    // Llamar al CORE
    pid_t pid = fork();
    if (pid == 0) {
        // Ejecutar CORE con core_id y operación
        execl("./core", "core", core_id_str.c_str(), operacion.c_str(), nullptr);
        perror("Error ejecutando core"); // Error si execl falla
        exit(1);
    }

    // Esperar el resultado del proceso hijo
    waitpid(pid, nullptr, 0);
}
