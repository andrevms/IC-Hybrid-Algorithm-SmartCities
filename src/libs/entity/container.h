#ifndef __CONTAINER_H_
#define __CONTAINER_H_
  
#include <stdlib.h>
#include <stdio.h>

#include <matrizAdjacente.h>
#include <passageiros.h>
#include <carro.h>
#include <pathTS.h>

struct container {
    Matriz m;
    Passageiros p;
    Carro c;
    int interactions;
    PathTS* pathList;
    Passageiros* passList;
    PathTS* path2optList;
    Passageiros* pass2optList;
};

/* Um Container é um ponteiro para o struct container, que armazena uma matriz m, uma quantidade de passageiros p e um veiculo c */
typedef struct container *Container;
 
//INIT's
/* Cria um passageiro com seus respectivos valores*/
Container containerInit(Matriz matriz, Passageiros pList, Carro carro, int interactions);

//Load Files
Container loadPath(const char fileName[], int interactions);

//Run
void run(Container ct);

//Free
void freeCTattributes(Container ct);

//PRINTS's
/* Imprime as informações do contanier*/
void containerPrint(Container ct);

#endif /* PASSAGEIRO_H_ */