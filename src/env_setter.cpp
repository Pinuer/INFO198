#include "env_setter.h"

void set_env_from_file(){
    vector<string> envFile = read_file("./.env");
    vector<string> fileLine;

    string env, envValue;
    string eraseCharacter = "'";


    for (string i : envFile){
        fileLine = split(i,"=");
        env = fileLine[0];
        envValue = remove_character(fileLine[1],eraseCharacter[0]);

        if(envValue.size() > 0) setenv(env.c_str(),envValue.c_str(),1);
        
    }

    
}

string get_enviroment_variable(const char* var) {
    char* valor = getenv(var);
    if (valor == nullptr) {
        cerr << "Error: La variable de entorno " << var << " no está definida." << endl;
        exit(1);  // Terminar el programa si falta alguna variable de entorno
    }
    return string(valor);
}