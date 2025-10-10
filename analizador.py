from decouple import config
import matplotlib.pyplot as plt
import numpy as np

print("INICIANDO PLOT")

#Obtiene las variables  de entorno
THREADS = config('ARRAY_THREADS')
DATA = config('DATOS')
REPETICIONES = int(config('REPETICIONES'))
GRAFICO = config('GRAFICO')


#Guarda los threads en una lista
tempList = THREADS.rsplit(",")
threadList = []

#pasa los threads a int y los guarda
for i in tempList:
    threadList.append(int(i))
print(threadList)

tempList.clear()


timeList = []
dataList = [] #Formato [[nthread1,rep1,rep2,...],[nthread2,rep1,rep2,...],...,[nthreadN,rep1,rep2,...]]

#Abre el archivo con los tiempos
f = open(DATA,'r')

#Guarda los tiempos en una lista
for i in f:
    timeList.append(float(i.replace("\n","")))
#Guarda los tiempos por repeticion en una lista temporal y los guarda en dataList(Lista con las Listas de los tiempos por repeticion)
if(len(timeList) != 0):
    for i in range(0,REPETICIONES):
        tempList.clear()
        for j in range(0,len(threadList)):
            tempList.append(timeList[j+(i*len(threadList))])
        dataList.extend([tempList.copy()])
    

    print(dataList)

    #Crea el grafico y  lo guarda en la direccion establecida
    for i in range (0,len(dataList)):
        plt.plot(threadList,dataList[i],label = "Repeticion " + str(i + 1),marker = "o")

    plt.title("Analisis de performance")
    plt.xlabel("Cantidad de threads")
    plt.ylabel("Tiempo en segundos")
    plt.grid()
    plt.legend()
    plt.savefig(GRAFICO)


    print("\n\nSe guardo el grafico en " + GRAFICO)

else:
    print("ERROR!, no hay data para analizar")
    

f.close()