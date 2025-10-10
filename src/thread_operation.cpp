#include "thread_operation.h"
#include "env_setter.h"
#include "func_string.h"

using namespace std;


pthread_mutex_t pthreadLock;
map<string, map<int, int>> conteoGlobal; // Map que mantiene el conteo por archivo
set<string> stopWords; // Palabras a ignorar

// Struct con el puntero del vector con las direcciones
struct fileOperation {
    vector<string>* filePathList;
    int* id;  
};

// Cargar stop words desde archivo
void cargarStopWords(string archivoStopWords) {
    ifstream archivo(archivoStopWords);
    string palabra;
    while (archivo >> palabra) {
        stopWords.insert(palabra);
    }
    archivo.close();
}

// Contar palabras en un archivo
map<string, int> contarPalabras(string filename) {
    map<string, int> cont;
    ifstream archivo(filename);

    if (!archivo.is_open()) {
        cerr << "No se puede abrir el archivo: " << filename << endl;
        return cont;
    }

    string palabra;
    while (archivo >> palabra) {
        for (char &c : palabra) {
            //if(c == 'Á' || c == 'É' || c == 'Í' || c == 'Ó' || c == 'Ú') c = accent_upper_to_lower(c);
            c = tolower(c); // Convertir a minúsculas
            

        }
        palabra = filter_string(palabra,LETTERS);
        if (stopWords.find(palabra) == stopWords.end()) { // Ignorar stop words
            cont[palabra]++;
        }
    }

    archivo.close();
    return cont;
}

// Actualizar el conteo global de palabras en un archivo
void actualizarConteoGlobal(map<string, int> &conteoPalabras, int id) {
    for (auto &[palabra, cantidad] : conteoPalabras) {
        conteoGlobal[palabra][id] += cantidad; // Asociamos la palabra con el ID del archivo
    }
}

// Función que imprime la ruta del archivo y realiza el conteo de palabras
void *print_file_path(void *threadOperation) {
    vector<string>* threadVector;
    int fileID;
    string filePath;
    pid_t tid = gettid();  // Obtener el ID del thread

    // Obtener el vector de archivos desde la estructura
    threadVector = ((struct fileOperation*)threadOperation)->filePathList;
    int* id = ((struct fileOperation*)threadOperation)->id;

    while (true) {
        pthread_mutex_lock(&pthreadLock); // Bloquea el acceso al vector

        if (threadVector->empty()) {
            pthread_mutex_unlock(&pthreadLock); // Desbloquea si ya no hay archivos
            break;
        }

        // Obtener la ruta del archivo y su ID
        filePath = threadVector->back();
        fileID = *id;
        threadVector->pop_back();
        (*id)++;

        pthread_mutex_unlock(&pthreadLock); // Desbloquea el acceso al vector

        // Contar palabras y actualizar el conteo global
        map<string, int> conteoPalabras = contarPalabras(filePath);
        pthread_mutex_lock(&pthreadLock); // Bloquear para actualizar el conteo global
        actualizarConteoGlobal(conteoPalabras, fileID);
        pthread_mutex_unlock(&pthreadLock); // Desbloquear

        // Escribir la salida en un archivo basado en el ID y la extensión
        string archivoSalida = getenv("OUTPUT_DIR") + string("/") + to_string(fileID) + "." + getenv("EXTENSION");
        ofstream outFile(archivoSalida);
        for (auto &[palabra, cantidad] : conteoPalabras) {
            if(palabra != "") outFile << palabra << "; " << cantidad << endl;
            
        }
        outFile.close();

        cout << "Archivo procesado: " << archivoSalida << " | Thread " << tid << endl;
    }


    return NULL;
}

// Función para abrir los hilos y asignarles la operación
void open_threads() {
    int cantThreads = stoi(get_enviroment_variable("CANTIDAD_THREAD"));
    pthread_t threads[cantThreads];
    int rc;

    // Crea el vector con las direcciones de los archivos a leer
    vector<string> filePathList;
    for (auto &ent : filesystem::directory_iterator(get_enviroment_variable("INPUT_DIR"))) {
        if (ent.path().extension() == "." + string(get_enviroment_variable("EXTENSION"))) {
            filePathList.push_back(ent.path().string());
            //cout << ent.path() << endl;
        }
    }

    if (filePathList.empty()) {
        cerr << "No se encontraron archivos con la extensión especificada en la carpeta de entrada." << endl;
        return;
    }

    // Asigna el puntero del vector y un contador de IDs a la estructura
    struct fileOperation threadOperation;
    threadOperation.filePathList = &filePathList;
    int id = 0;
    threadOperation.id = &id;

    // Mutex para la sincronización de los hilos
    if (pthread_mutex_init(&pthreadLock, NULL) != 0) {
        cerr << "Error: No se pudo inicializar el mutex." << endl;
        return;
    }

    // Crear los hilos
    for (int i = 0; i < cantThreads; i++) {
        rc = pthread_create(&threads[i], NULL, print_file_path, (void *)&threadOperation);

        if (rc) {
            cerr << "Error: No se pudo crear el thread " << rc << endl;
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < cantThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&pthreadLock); // Destruir el mutex

}



// Crear el archivo mapa_archivo
void crearMapaArchivo() {    
    int id = 0;
    string archivoMapa = get_enviroment_variable("MAPA_ARCHIVOS"); // Obtener la ruta desde la variable de entorno MAPA_ARCHIVOS
    string directorioEntrada = get_enviroment_variable("INPUT_DIR"); // Directorio de entrada donde se encuentran los archivos a procesar

    ofstream mapaArchivo(archivoMapa);// Abrir el archivo de salida mapa_archivo

    if (!mapaArchivo.is_open()) {
        cerr << "Error al crear el archivo mapa_archivo en: " << archivoMapa << endl;
        return;
    }

    for (auto &ent : filesystem::directory_iterator(directorioEntrada)) {
        if (ent.path().extension() == "." + string(getenv("EXTENSION"))) {
            mapaArchivo << ent.path().stem().string() << ", " << id << endl;// Escribir en el archivo el nombre del archivo (sin la extensión) y su ID
            id++;
        }
    }

    mapaArchivo.close();
    cout << "Archivo mapa_archivo creado exitosamente en: " << archivoMapa << endl;
}

