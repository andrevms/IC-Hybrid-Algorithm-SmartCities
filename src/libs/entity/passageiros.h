#ifndef __PASSAGEIRO_H_
#define __PASSAGEIRO_H_
  
#include <stdlib.h>
#include <stdio.h>
#include <pathTS.h>
#include <carro.h>

struct passageiros {
    int* origem;
    int* destino;
    float* valorMaximo;
    float* valorPago;
    int listSize;
};

/* Um Matriz é um ponteiro para uma matrizAdjacente, ou seja, uma Matriz contém o endereço de um matrizAdjacente. */
typedef struct passageiros *Passageiros;
 
//INIT's
/* Cria um passageiro com seus respectivos valores*/
Passageiros pListInit(int* entry, int* out, float* value, float* payValue, int size);

//FUNCTION's

/*Retorna um array de passageiros que satisfazem o path*/
Passageiros pListOnPath(Passageiros p, PathTS path, Carro c);

//PRINTS's
/* Imprime as informações do passageiro*/
void passageiroPrint(Passageiros p);
 
#endif /* PASSAGEIRO_H_ */