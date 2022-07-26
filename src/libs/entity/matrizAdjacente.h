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
Matriz MATRIZinit_int(int row, int col, int* vetor);
/* Inicia os tamanhos da matriz de adjacencia e seu vetor com todas as entradas com o valor val */
Matriz MATRIZinit_intVal(int row, int col, int val);

//PRINTS's
/* Imprime as informações do matriz de inteiros: size_x; size_y; nodeVal -> size = [row * cow] */
void MATRIZprint_int(Matriz m);
 
#endif /* MATRIZ_ADJACENTE_H_ */