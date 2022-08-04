#ifndef __PATH_TS_H_
#define __PATH_TS_H_
  
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <matrizAdjacente.h>

struct travellingSalesmanPath {
    void* path;
    void* value;
    void* totalValue;
    int pathSize;
};


/* Um PathTS é um ponteiro para uma travellingSalesmanPath*/
typedef struct travellingSalesmanPath *PathTS;
 
//INIT's
PathTS initPathTS_int(int* pathCaminho, int* valuePath, int pathTamanho);

//FUNCTIONS
//Retorna um caminho randomizado aleatorio
PathTS generateRandomPathTS_int(Matriz m);

PathTS optimize2opt(PathTS path, Matriz m);

int* swap2opt(PathTS pTS, int swapBegin, int swapEnd);

int positionValue_int(void* path, int size, int number);
int pathValue_int(void* pathValues, int size);
int pTSValue_int(void* pathValues, int init, int end);
int pathValue(int* path, int size);

//Retorna um caminho aleatorio guloso 
PathTS generateRandGulosoPathTS_int(Matriz m);

//retorna um array com o caminho selecionado de forma aleatoria e gulosa utilizando os pesos das entradas para selecionar o caminho 
int* arrayRandGuloso_int(Matriz m);
/*Calcula o valor total dos pesos do path recebido*/
int pathValue(int* path, int size);


//PRINTS's
void PathTSprint_int(PathTS p);
 
#endif /* CAMINHO_H_ */