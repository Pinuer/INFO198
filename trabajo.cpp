#include <iostream>
#include <unistd.h>

using namespace std; 

int main(int argc, char *argv[]){
    int c;
    
    char* arg_u = nullptr;
    char* arg_p = nullptr;
    char* arg_t = nullptr;
    char* arg_v = nullptr;
    char* arg_n = nullptr;



    while ((c = getopt(argc, argv, "u:p:t:v:n:")) != -1) {
        switch (c) {
            case 'u':
            arg_u = optarg; 
            cout << arg_u << endl;
            break;

            case 'p':
            arg_p = optarg; 
            cout << arg_p << endl;
            break;

            case 't':
            arg_t = optarg; 
            cout << arg_t << endl;
            break;

            case 'v':
            arg_v = optarg; 
            cout << arg_v << endl;
            break;

            case 'n':
            arg_n = optarg; 
            cout << arg_n << endl;
            break;

            default:
                cout<<"-u usuario -p contraseña -t frase -v vector -n número\n";
                break;

        }
    }
}