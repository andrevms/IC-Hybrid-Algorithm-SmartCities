#ifndef __CONTAINER_H_
#define __CONTAINER_H_
  
#include <stdlib.h>
#include <stdio.h>

#include<matrizAdjacente.h>
#include<passageiros.h>
#include<carro.h>

struct container {
    Matriz m;
    Passageiros p;
    Carro c;
};

/* Um Matriz é um ponteiro para uma matrizAdjacente, ou seja, uma Matriz contém o endereço de um matrizAdjacente. */
typedef struct container *Container;
 
//INIT's
/* Cria um passageiro com seus respectivos valores*/
Container containerInit(Matriz matriz, Passageiros pList, Carro carro);

//PRINTS's
/* Imprime as informações do passageiro*/
 
#endif /* PASSAGEIRO_H_ */