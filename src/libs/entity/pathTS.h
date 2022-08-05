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
    int numPassengersOnPath;
    int pathSize;
};

/*
 * \brief Um PathTS é um ponteiro para uma travellingSalesmanPath
 * \param path void* --> armazena o caminho gerado inicia em 0 e termina em 0
 * \param value void* --> armazena os valores do caminho, seu tamanho é pathSize-1
 * \param totalValue void* --> armazena a soma dos valores de value.
 * \param numPassengersOnPath Integer --> armazena o numero de passageiros que podem embarcar no caminho
 * \param pathSize Integer --> Tamanho do array path 
 * 
 * \info Object should be dealloc by user
 */
typedef struct travellingSalesmanPath *PathTS;
 
//INIT's

/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
PathTS initPathTS_int(int* pathCaminho, int* valuePath, int pathTamanho);

//FUNCTIONS

//Retorna um caminho randomizado aleatorio
/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
PathTS generateRandomPathTS_int(Matriz m);

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
int positionValue_int(void* path, int size, int number);

/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
int pathValue_int(void* pathValues, int size);

/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
int pTSValue_int(void* pathValues, int init, int end);

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

//Retorna um caminho aleatorio guloso 
/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
PathTS generateRandGulosoPathTS_int(Matriz m);

//retorna um array com o caminho selecionado de forma aleatoria e gulosa utilizando os pesos das entradas para selecionar o caminho 
/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
int* arrayRandGuloso_int(Matriz m);
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
void printPathTS_int(PathTS p);
 
#endif /* CAMINHO_H_ */