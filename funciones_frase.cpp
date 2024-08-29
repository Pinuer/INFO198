#include "funciones_frase.h"
#include <iostream>
#include <string.h>
#include <algorithm> 

void palindromo(const string &f){
    string frase;
    for (int i = 0; i < f.length(); ++i) {
        char f_m = tolower(f[i]);
        // Verificar si el carácter es una letra (mayúscula o minúscula)
        if ((f_m >= 'a' && f_m <= 'z')) {
            frase += f_m; // Convertir a minúscula y agregar a la cadena limpia
        }
    }
    
    // Crear una versión invertida de la cadena limpia
    string invertida = frase;
    reverse(invertida.begin(), invertida.end()); // Invertir la cadena

    // Comparar la cadena limpia con su versión invertida
    if (frase == invertida) {
        cout<<"Es un palíndromo!!"<<endl;
    } else {
        cout<<"NO es un palíndromo!!"<< endl;
    }
 
}

int ContarVocales(const string &f){
    int c = 0;
    for (int i = 0; i < f.length(); ++i) {
        // Convertir el carácter a minúscula para simplificar la comparación
        char f_m = tolower(f[i]);
        if (f_m == 'a' || f_m == 'e' || f_m == 'i' || f_m == 'o' || f_m == 'u') {
            c++;
        }
    }
    return c;
}

int ContarLetras(const string& f) {
    int c = 0;
    for (int i = 0; i < f.length(); i++) {
        // Convertir el carácter a minúscula para simplificar la comparación
        char lower_c = tolower(f[i]);
        if (lower_c >= 'a' && lower_c <= 'z'){
            c++;
        }
    }
    return c;
}
