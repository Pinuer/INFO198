#include "common.h"
#include "func_string.h"


//Chekea si el valor ingresado es un numero
bool check_num(string num){
  if(num.empty() || num.find_first_not_of(DIGITS) != string::npos){
    return false;
  }
  return true;
}

//Menu del programa
string opt_menu(string user, bool admin, bool checkIndex){
  string opt;
  print_separation();
  cout << "SISTEMA " << getpid() << endl;
  cout << "Usuario: " << user <<endl;
  if(admin){//Para imprimir el rol, mira si es admin o no
    cout << "Rol: Admin" << endl;
  }
  else{
    cout << "Rol: Usuario generico" << endl;
  }

  print_separation();
  cout << "1.Detectar Palindrome" << endl;
  cout << "2.Contar Vocales" << endl;
  cout << "3.Contar letras en un texto" << endl;
  cout << "4.Sumatoria y promedo de un vector" << endl;
  cout << "5.Calcular f(x)=5x*x+1/x" << endl;
  cout << "6.Contar Palabras" << endl;
  cout << "7.Conteo Paralelo con threads" << endl;
  if(checkIndex) cout << "8.Crear Indice invertido" << endl;
  cout << "9.Analisis de performance" << endl;
  cout << "10.Planificador" << endl;
  cout << "20.Buscador" << endl;
  if(admin){
    cout << "\n98.Lista de Usuarios" << endl;
    cout << "99.Ingresar Usuario" << endl;
    cout << "100.Elimunar Usuario" << endl;
  }
  cout << "\n0.Salir\n" << endl;
  cout << "Ingrese opcion: ";
  cin >> opt;
  if(opt.empty() || opt.find_first_not_of(DIGITS) != string::npos){
    cout << "No es un numero, Ingrese una de las opciones\n" << endl;
    return opt_menu(user, admin, checkIndex);
  }
  return opt;
}

//Checkea si la entrada es vacia
bool check_empty(string s){
  if(s.size() == 0) return true;
  return false;
}

//Toma el string de numeros separado por un separador y devuelve un vector que contiene los numeros separados
vector<int> split_num(string s, string separator){
    vector<int> values = {};
    size_t pos = 0; //size_t = maximo tamaño posible de cualquier objeto
    string temp;
    if(s[s.size()-1] == separator[0]) s.erase(s.size() - 1);
    while((pos = s.find(separator)) != string::npos){//npos = valor que representa el ultimo numero de size_t, find devuelve la posicion donde primero encuentra una coincidencia
        temp = s.substr(0,pos);
        values.push_back(stoi(temp));
        s.erase(0, pos + separator.length());
    }
    values.push_back(stoi(s));

    return values;
}

vector<string> split(string s, string separator){
  vector<string> splitedVector = {};
  size_t pos = 0;
  string temp;
  if (s[s.size()-1] == separator[0]) s.erase(s.size()-1);
  while((pos = s.find(separator)) != string::npos){
    temp = s.substr(0,pos);
    splitedVector.push_back(temp);
    s.erase(0,pos + separator.length());
  }
  splitedVector.push_back(s);

  return splitedVector;
}


//Cuenta los simbolos en un string comparandolos con un string filtro
int count_symbols(string s, string filter){
  int count = 0;
  for(int i = 0; i < s.size(); i++){
    if (filter.find(s[i]) != string::npos) count++;
  }
  return count;
}

//Checkea si el string ingresado es palidrome
bool check_pali(string s){
  s = text_normalization(s);
  for(int i = 0; i < s.size()/2; i++ ){
    if(s[i] != s[(s.size()-1)-i]){
      return false;
    }
  }
  return true;
}

//Cambia las mayusculas a minusculas y elimina los espacios en blanco
string text_normalization(string s){
  for (int i = 0; i < s.size(); i++){
    if(isupper(s[i])){
      s[i] = tolower(s[i]);
    }else if(s[i] == ' '){
      s.erase(i,1);
      i--;
    }
    
  }
  return s;
}

//Muestra la lista de los usuarios
void print_user_list(vector<tuple<string,string>> userVector){
  int j = 0, sizeUser = 0;
  string tempUser = "", tempType = "";
  string printUser = "Usuario", printType = "||Rol", separation = "-";
  string adm = "Admin", userg = "Usuario Generico";


  for (tuple<string,string> i : userVector){
    if(j >= 100) break;
    if (sizeUser < get<0>(i).size()) sizeUser = get<0>(i).size();
    j++;
  }
  sizeUser++;
  j = 0;

  while(printUser.size() < sizeUser) printUser += " ";
  cout << printUser + printType << endl;
  while(separation.size() < sizeUser) separation += "-";
  separation += "|";
  while(separation.size() < (sizeUser + userg.size() + 1))separation += "-";

  cout << separation << endl;

  for (tuple<string,string> i : userVector){
    if (j >= 100) break;
    tempUser = get<0>(i);

    while (tempUser.size() < sizeUser) tempUser += " ";

    if(get<1>(i) == "admin") tempType = adm;
    else if(get<1>(i) == "genuser") tempType = userg;
    else tempType = "No definido";

    cout << tempUser + "|" + tempType << endl;
    j++;
  }
}

//remueve todas las ocurrencias de un caracter en un string
string remove_character(string input, char c){
  string output = "";
  if(input.size() != 0){
    for (int i = 0; i < input.size(); i++){
      if(c != input[i]) output += input[i];
    }
  }
  return output;
}

//Regresa el string sin los simbolos que no se encuentren en el filtro
string filter_string(string input, string filter){
  string output = "";
  for(int i = 0; i < input.length(); i++) {
    if(filter.find(input[i]) != string::npos && input[i] != '�') output += input[i];
  }
  return output;
}

/*char accent_upper_to_lower(char c){
  if (c = 'Á') return 'á';
  if (c = 'É') return 'é';
  if (c = 'Í') return 'í';
  if (c = 'Ó') return 'ó';
  if (c = 'Ú') return 'ú';
}*/


//Impriem una linea para separar las ejecuciones del sistema
void print_separation(){
  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
}