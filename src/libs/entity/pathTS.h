#ifndef __PATH_TS_H_
#define __PATH_TS_H_
  
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <matrizAdjacente.h>

struct travellingSalesmanPath {
    void* path;
    void* totalValue;
    int numPassengersOnPath;
    int pathSize;
};

/*
 * \brief Um PathTS é um ponteiro para uma travellingSalesmanPath
 * \param path void* --> armazena o caminho gerado inicia em 0 e termina em 0
 * \param totalValue void* --> armazena a soma dos pesos do caminho
 * \param numPassengersOnPath Integer --> armazena o numero de passageiros que podem embarcar no caminho
 * \param pathSize Integer --> Tamanho do array path 
 * 
 * \info Object should be dealloc by user
 */
typedef struct travellingSalesmanPath *PathTS;
 
//INIT's

/* \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 */
PathTS iPathTS_int(int* pathCaminho, int* valuePath, int pathTamanho);

PathTS initPathTS_int(int* pathCaminho, int* valuePath, int pathTamanho, int numPassengers);

//FUNCTIONS

int calculePathValue(int* pathCaminho, int pathTamanho, Matriz m);
int sumArrayElements(int* path, int size);
 
int positionValue_int(void* path, int size, int number);
int pTSValue_int(void* pathValues, int init, int end, Matriz m);

//PRINTS's

void printPathTS_int(PathTS p, Matriz m, int contador);
void printPathTSInFile_int(const char fileName[], PathTS p, Matriz m, int contador);
void freePath(PathTS pTS);
PathTS copyPath(PathTS pTS);

#endif /* CAMINHO_H_ */