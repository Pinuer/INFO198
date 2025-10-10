#include"func_core.h"


void calcular(int core_id, string& operacion) {
    ofstream resultados(getenv("RESULTADOS"), ios::app);
    string op;
    double num1, num2;

    stringstream ss(operacion);
    string temp;
    
    getline(ss, temp, ';'); // ID
    getline(ss, op, ';'); // Operación
    getline(ss, temp); // Números

    // Parsear números
    size_t comma_pos = temp.find(',');
    num1 = stod(temp.substr(0, comma_pos));
    num2 = stod(temp.substr(comma_pos + 1));

    double resultado = 0;
    if (op == "suma") {
        resultado = num1 + num2;
    } 
    else if (op == "resta") {
        resultado = num1 - num2;
    } 
    else if (op == "division") {
        resultado = num2 != 0 ? num1 / num2 : 0;
    } 
    else if (op == "multiplicacion") {
        resultado = num1 * num2;
    }

    // Escribir el resultado junto con el core_id en el archivo
    resultados << "(" << core_id << ": " << operacion << ") => " << resultado << endl;
}