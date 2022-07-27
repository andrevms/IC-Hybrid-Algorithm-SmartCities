#ifndef __CONTAINER_H_
#define __CONTAINER_H_
  
#include <stdlib.h>
#include <stdio.h>

#include <matrizAdjacente.h>
#include <passageiros.h>
#include <carro.h>

struct container {
    Matriz m;
    Passageiros p;
    Carro c;
};

/* Um Container é um ponteiro para o struct container, que armazena uma matriz m, uma quantidade de passageiros p e um veiculo c */
typedef struct container *Container;
 
//INIT's
/* Cria um passageiro com seus respectivos valores*/
Container containerInit(Matriz matriz, Passageiros pList, Carro carro);

//PRINTS's
/* Imprime as informações do contanier*/
void containerPrint(Container ct);
 
#endif /* PASSAGEIRO_H_ */