#ifndef __CARRO_H_
#define __CARRO_H_
  
#include <stdlib.h>
#include <stdio.h>

#include<passageiros.h>

struct carro {
    int num_passageiros;
    int passageirosNoCarro;
    int* listPassageiro;
};

/* Um Matriz é um ponteiro para uma matrizAdjacente, ou seja, uma Matriz contém o endereço de um matrizAdjacente. */
typedef struct carro *Carro;
 
//INIT's
/* Cria um passageiro com seus respectivos valores*/
Carro carroInit(int num_passageiros);

//PRINTS's
/* Imprime as informações do passageiro*/
void carroPrint(Carro c);
 
#endif /* PASSAGEIRO_H_ */