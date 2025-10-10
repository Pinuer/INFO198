#include "func_cont.h"
#include <iostream>
#include <string>
#include <unistd.h>  
#include <filesystem>

using namespace std;

int main(int argc, char** argv) {
    string ext, entrada, salida;
    bool verificar = false;

    cout<<"PID: "<<getpid()<<endl;

    int opcion;
    do {
        cout<<"\nSeleccione una opción:"<<endl;
        cout<<"\n(0) Salir"<<endl;
        cout<<"(1) Extensión de archivos a procesar (ej: txt)"<<endl;
        cout<<"(2) Path de carpeta a procesar (ej: /home/lvc/in)"<<endl;
        cout<<"(3) Path de carpeta que contendrá la respuesta del proceso (ej: /home/lvc/out)"<<endl;
        cout<<"(4) Procesar"<<endl;
        cout<<"\nOpción: ";
        cin>>opcion;

        switch (opcion) {
            case 0: {
                cout<<"Saliendo del programa"<<endl;
                break;
            }

            case 1: {
                cout<<"Ingrese la extensión de los archivos: ";
                cin>>ext;
                verificar = true;
                break;
            }

            case 2: {
                cout<<"Ingrese el path de la carpeta a procesar: ";
                cin>>entrada;
                
                if (!std::filesystem::exists(entrada) || !std::filesystem::is_directory(entrada)) {
                    cout<<"La carpeta de entrada NO EXISTE!!"<<endl;
                    verificar = false;
                } 
                
                else {
                    verificar = true;
                }
                break;
            }

            case 3: {
                cout<<"Ingrese el path de la carpeta que contendrá la respuesta del proceso: ";
                cin>>salida;

                if (!std::filesystem::exists(salida)) {
                    cout<<"La carpeta de salida NO EXISTE!!"<<endl;
                    verificar = false;
                } 
                
                else {
                    verificar = true;
                }

                break;
            }

            case 4: {
                if (ext.empty() || entrada.empty() || salida.empty() || !verificar) {
                    cout<<"Ingrese datos válidos para procesar los archivos"<<endl;
                }

                else {
                    procesarArchivos(ext, entrada, salida);
                }

                break;
            }

            default: {
                cout<<"Opción no válida. Por favor seleccione una opción válida"<<endl;
            }
        }
    } while (opcion != 0);

    return 0;
}
