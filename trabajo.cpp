#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

using namespace std; 

struct Args {
    string usuario;
    string contrasena;
    string frase;
    string vectorStr;
    double numero;
};

void mostrarMenu(const Args& args);

int main(int argc, char *argv[]) {
    
    int c; 
    Args args;
    
    while ((c = getopt(argc, argv, "u:p:t:v:n:")) != -1) {
        switch (c) {
            case 'u':
                args.usuario = optarg; 
                break;
            case 'p':
                args.contrasena = optarg; 
                break;
            case 't':
                args.frase = optarg; 
                break;
            case 'v':
                args.vectorStr = optarg; 
                break;
            case 'n':
                try {
                    args.numero = stod(optarg);
                } catch (const exception& e) {
                    cerr << "Error al convertir el número: " << e.what() << "\n";
                    return 1;
                }
                break;
            default:
                cout << "Uso: -u usuario -p contraseña -t frase -v vector -n número\n";
                return 1;
        }
    }

    if (args.usuario.empty() || args.contrasena.empty() || args.frase.empty() || args.vectorStr.empty() || args.numero == 0) {
        cout << "Todos los argumentos (-u, -p, -t, -v, -n) son requeridos.\n";
        return 1;
    }

    // Mostrar el menú
    mostrarMenu(args);
    return 0;
}



// Función que muestra el menú y maneja las opciones seleccionadas
void mostrarMenu(const Args& args) {
    int opcion;
    do {
        cout << "\nSeleccione una opción de menú:\n";
        cout << "1) Detección de palíndromos\n";
        cout << "2) Contar vocales\n";
        cout << "3) Contar letras en un texto\n";
        cout << "4) Promedio y sumatoria de un vector\n";
        cout << "5) Calcular f(x) = 5x^2 + 1/x\n";
        cout << "6) Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:{
                cout<<5<<endl;
                break;
            }
            case 2:{
                cout << 4<<endl;
                break;
            }
            case 3:{
                cout << 3<<endl;
                break;
            }
            case 4: {
                cout<<2<<endl;
                break;
            }
            case 5:{
                cout<<1<<endl;
                break;
            }
            case 6:{
                cout << "Saliendo del programa.\n";
                break;
            }
            default:{
                cout << "Opción inválida. Intente de nuevo.\n";
                break;
            }
        }
    } while (opcion != 6);
}
