#include <sys/wait.h>
#include "common.h"
#include "file_operation.h"
#include "func_string.h"

void program(int rep, vector<string> tempArray, int ogThreads, string datos, string grafico){

    //Variables para cronometrar los pocesos
    struct timespec timeBegin, timeEnd;
    long sec, nanosec;
    double timeElapsed;

    //Vector con la cantidad de threads en int
    vector<int> threadArray = {};
    for(string i : tempArray) threadArray.push_back(stoi(i));

    cout << "PID EJECUTADOR: " << getpid() << endl;
    cout << "Iniciando analisis de performance" << endl << endl;

    //Borra los datos que estaban antes de ejecutar este proceso
    erase_file_contents(datos);

    //Checkea si hay 2 o mas repeticiones
    if(rep < 2){
        cout << "ERROR! Insuficientes repeticiones" << endl;
    }else{
      //For loop por la cantidad de repeticiones
      for(int j = 0; j < rep; j++){
      
        cout << "\nRepeticion: " << j << endl;
            
        //For loop por la cantidad de threads en el arreglo de threads
        for(int i : threadArray){
          setenv("CANTIDAD_THREAD",to_string(i).c_str(),1);
          //Comienza a cronometrar
          clock_gettime(CLOCK_REALTIME, &timeBegin);
          pid_t pid = fork(); //Crear un proceso hijo
          if (pid == 0) { 
            execl("./contar_paralelo", "contar_paralelo", NULL);
            exit(0); 
          }
          
          else if (pid > 0) {
            wait(NULL); 
          } 
          
          else {
            cout<<"Error al crear el proceso"<<endl;
          }
          //Termina de cronometrar
          clock_gettime(CLOCK_REALTIME, &timeEnd);

          sec = timeEnd.tv_sec - timeBegin.tv_sec;
          nanosec = timeEnd.tv_nsec - timeBegin.tv_nsec;
                
          timeElapsed = sec + nanosec*1e-9;
          //Guarda el tiempo en el archivo datos
          add_line_to_file(datos,to_string(timeElapsed) + "\n");
        }
              
      }
      cout  << endl;

      
      // llama a analizador.py para crear el grafico con los tiempos
      pid_t pid = fork(); //Crear un proceso hijo
      if (pid == 0) { 
        char *interpreter = "python3";
        char *pythonPath = "./analizador.py";
        char *argumentList[] = {interpreter,pythonPath,NULL};
        execvp(interpreter,argumentList);
        exit(0); 
      }
          
      else if (pid > 0) {
        wait(NULL); 
      } 
          
      else {
        cout<<"Error al crear el proceso"<<endl;
      }

      setenv("CANTIDAD_THREAD",to_string(ogThreads).c_str(),1); //Restora la cantidad de threads original

    }
}

int main(int argc, char** argv){

  int rep = stoi(argv[0]);
  vector<string> threadArray = split(argv[1],",");
  int ogThreads = stoi(argv[2]);
  string datos = argv[3];
  string grafico = argv[4];

  

  program(rep,threadArray,ogThreads,datos,grafico);

  return 0;
}