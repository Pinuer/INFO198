#include "func_math.h"

//Sumatoria de un vector de numeros enteros
int summation(vector<int> numbers){
    int sum = 0;
    for(int i : numbers){
        sum += i;
    }
    return sum;
}

//Promedio de un vector de numeros enteros
float average(vector<int> numbers){
    float sum = summation(numbers);
    return sum/numbers.size();
}

//Calcula la funcion
float calc_func(float n){
    if(n == 0){
        cout << "No se pudo realizar la operacion (Division por cero)" << endl;
        return 0;
    }
    else return ((5*n)*n) + 1/n;
}