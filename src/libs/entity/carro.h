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

/* Um Carro é um ponteiro para uma struct carro */
typedef struct carro *Carro;
 
//INIT's
/* Cria um carro que pode receber um valor maximo de num_passageiros ao mesmo tempo*/
Carro carroInit(int num_passageiros);

//PRINTS's
/* Imprime as informações do carro*/
void carroPrint(Carro c);
 
#endif /* PASSAGEIRO_H_ */