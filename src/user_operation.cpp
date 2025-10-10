#include "user_operation.h"



//Checkea si las credenciales ingresadas son correctas
bool check_login(string user, string password, bool* admin, string userFilePath){
  vector<tuple<string,string,string>> userVector = {};
  if (user.size() < 3 ||  count_symbols(user,LETTERS) < user.size()){ //Checkea si el usuario ingresado tenga 3 o mas simbolos y que sean todos letras
    cout << "ERROR!, Usuario o contraseña incorrectos\n" << endl;
    return false;
  }else if (password.size() < 8 || (count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < password.size() ||(count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < 6){//Chequea que la contraseña tenga 8 o mas simbolos y que no existan caracteres especiales
    cout << "ERROR!, Usuario o contraseña incorrectos\n" << endl;
    return false;
  }else{
    userVector = get_user_login(userFilePath);
    for(tuple<string,string,string> i : userVector){
      if(get<0>(i) == user && get<1>(i) == password){ //Verifica si el usuario y contraseña coinciden y si es admin
        if(get<2>(i) == "admin") *admin = true;
        return true;
      }
      
    }
    cout << "ERROR!, Usuario o contraseña incorrectos exit\n" << endl;//Sale si no encuentra ningun usuario y contraseña que coincida
    return false;
  } 
  
}

//Saca los usuarios y sus respectivos elementos del archivo
vector<tuple<string,string,string>> get_user_login(string fileName){
  vector<tuple<string,string,string>> userVector = {}; 

  vector<string> read = read_file(fileName);
  vector<string> tempUser = {};
  tuple<string,string,string> tempTuple = {};

  
  for(string i : read){
    tempUser = split(i,",");
    tempTuple = {tempUser[0],tempUser[1],tempUser[2]};
    userVector.push_back(tempTuple);
    tempUser = {};
    tempTuple = {};
  }

  return userVector;
}

vector<tuple<string,string>> get_user_list(string fileName){
  vector<tuple<string,string>> userVector = {}; 

  vector<string> read = read_file(fileName);
  vector<string> tempUser = {};
  tuple<string,string> tempTuple = {};

  
  for(string i : read){
    tempUser = split(i,",");
    tempTuple = {tempUser[0],tempUser[2]};
    userVector.push_back(tempTuple);
    tempUser = {};
    tempTuple = {};
  }

  return userVector;
}

void add_user(string userFilePath){
  string newUser = "";
  string user, password, temp, role;
  bool check;
  vector<tuple<string,string>> userVector = get_user_list(userFilePath);
  do{
    cout << "Insgrese nombre de usuario nuevo (Tamaño minimo: 3, Solo letras): ";
    cin >> user;
    if(user.size() < 3 ||  count_symbols(user,LETTERS) < user.size()){
      cout << "Error! Nombre de usuario ingresado no cumple con condiciones" << endl;
      check = false;
    }
    else check = true;
  }while(!check);

  do{
    cout << "Ingrese contraseña: ";
    cin >> password;
    if (password.size() < 8 || (count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < password.size() ||(count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < 6){//Chequea que la contraseña tenga 8 o mas simbolos y que no existan caracteres especiales
      cout << "ERROR! contraseña no cumple con requisitos" << endl;
      check = false;
    }
    else check = true;
  }while(!check);
  do{
    cout <<"1.-Admin\n2.-Usuario generico" << endl;
    cout << "Ingrese rol(Numero de la opcion):";
    cin >> temp;
    if(temp == "1"){
      role = "admin";
      check = true;
    } 
    else if(temp == "2") {
      role = "genuser";
      check = true;
    } 
    else{
      cout << "ERROR! se ingreso opcion no aceptada" << endl;
      check = false;
    }
  }while(!check);
  for (tuple<string,string> i : userVector){
    if (get<0>(i) == user){
      cout << "ERROR! usuario ya se encuentra en la lista" << endl;
      return;
    }
  }
  newUser = user + "," + password + "," + role;
  
  add_user_to_file(userFilePath,newUser);
}

void erase_user(string userFilePath){
  bool check = false;
  string temp, user;
  do{
    cout << "Se va a eliminar un usuario, ¿Esta seguro?(Y/N): ";
    cin >> temp;
    if (temp != "Y" && temp != "N" && temp != "y" && temp != "n"){
      cout << "ERROR! no se ingreso la opcion correcta" << endl;
    }
    else check = true;
  }while(!check);
  if(temp == "Y" || temp == "y"){

    vector<string> read = read_file(userFilePath);
    vector<string> tempUser = {};
    vector<string> fileIn = {};
    bool check = true;

    cout << "Ingrese nombre de usuario: ";
    cin >> user;

    for (string i : read){
      tempUser = split(i,",");
      if(user == tempUser[0]){
        if(tempUser[2] == "admin"){
          cout << "\nNo se pudo eliminar usuario" << endl;
          check = false;
          break;
        }
      }
      else{
        fileIn.push_back(i);
      }
    }
    if(check){
      if(fileIn.size() == read.size()) cout << "\nNo se encontro Usuario" << endl;
      else {
        erase_lines(userFilePath,fileIn);
        cout << "\nSe elimino Usuario " << user << endl; 
      }
    }

  }
}