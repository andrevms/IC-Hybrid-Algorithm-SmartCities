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
PathTS initPathTS_int(int* pathCaminho, int* valuePath, int pathTamanho);

PathTS callocPathTS_int(int pathSize);
//FUNCTIONS

int calculePathValue(int* pathCaminho, int pathTamanho, Matriz m);
/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
PathTS optimize2opt(PathTS path, Matriz m);
PathTS iPathTS_int(int* pathCaminho, int* valuePath, int pathTamanho);
/*
 * \brief 
 * \param pTS PathTS Pointer --> Caminho a ser reordenado
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
void* swap2opt(PathTS pTS, int swapBegin, int swapEnd);

int* swap2opt_int(int* path, int pathSize, int swapBegin, int swapEnd);


/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
int sumArrayElements(int* path, int size);

/*Calcula o valor total dos pesos do path recebido*/

/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
int sumArrayElements(int* path, int size);


//PRINTS's

/*
 * \brief Write PathTS Informations to stdout
 * \param PathTS travellingSalesmanPath Pointer --> travellingSalesmanPath that will be printed
 */
void printPathTS_int(PathTS p, Matriz m);

/*
 * \brief Write PathTS Informations on the end of a file
 * \param fileName --> Name of the file that will be write
 * \param PathTS travellingSalesmanPath Pointer --> travellingSalesmanPath that will be printed
 */
void printPathTSInFile_int(const char fileName[], PathTS p, Matriz m, int contador);

void freePath(PathTS pTS); 
int positionValue_int(void* path, int size, int number);


int pTSValue_int(void* pathValues, int init, int end, Matriz m);


#endif /* CAMINHO_H_ */