#ifndef __MATRIZ_ADJACENTE_H_
#define __MATRIZ_ADJACENTE_H_
  
#include <stdlib.h>
#include <stdio.h>

struct matrizAdjacente {
    int size_x;
    int size_y;
    void* nodeVal;
};

/* Um Matriz é um ponteiro para uma matrizAdjacente, ou seja, uma Matriz contém o endereço de um matrizAdjacente. */
typedef struct matrizAdjacente *Matriz;
 
//INIT's

/* Inicia os tamanhos da matriz de adjacencia : size_x = row; size_y = col; e atribui vetor a m->nodeVal*/
/*
 * \brief Inicializa uma matriz de adjacencia com linha, coluna e vetor recebidos.
 * \param row Integer --> Number of rows.
 * \param col Integer --> Number of columns.
 * \param vetor Integer Pointer --> Array with matriz values. Size equal rows * columns.
 * \return A Pointer for an object Matriz initialized with params.
 * \info Object should be dealloc by user
 */
Matriz initMatrizWithArray_int(int row, int col, int* vetor);

/*
 * \brief Inicializa uma matriz de adjacencia com linha, coluna e vetor recebidos.
 * \param row Integer --> Number of rows.
 * \param col Integer --> Number of columns.
 * \param val Integer --> Valor que o vetor ira receber em todas as entradas. Size equal rows * columns.
 * \return A Pointer for an object Matriz initialized with params.
 * \info Object should be dealloc by user
 */
Matriz initMatrizWithVal_int(int row, int col, int val);

/*
 * \brief Inicializa uma matriz de adjacencia com calloc.
 * \return A Pointer for an object Matriz.
 * \info Object should be dealloc by user
 */
Matriz initMatriz();


//FUNCTIONS

/*
 * \brief Grab a given row from a Matriz.
 * \param m Matriz --> Matriz .
 * \param row Integer --> Number of the row selected.
 * \param vetor Integer Pointer --> Array with matriz values. Size equal rows * columns.
 * \return A Integer Pointer with the row values selected .
 * \info Object should be dealloc by user
 */
int* getRowValues_int(Matriz m, int row);

/*
 * \brief Grab an elemento from Matriz.
 * \param m Matriz --> Matriz adjacente com os valores ja inicializados.
 * \param row Integer --> Number of the row selected.
 * \param col Integer --> Number of the col selected.
 * \return A Integer with the value of the [row][col] selected .
 */
int getElementValue_int(Matriz m, int row, int col);

//PRINTS's

/*
 * \brief Write Matriz info on stdout
 * \param m Matriz --> Matriz adjacente with values [NOT NULL].
 */
void printMatriz_int(Matriz m);
 
#endif /* MATRIZ_ADJACENTE_H_ */