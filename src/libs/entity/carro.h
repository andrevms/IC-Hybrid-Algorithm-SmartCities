#ifndef __CARRO_H_
#define __CARRO_H_
  
#include <stdlib.h>
#include <stdio.h>

struct carro {
    int numMaxPassageiros;
};

/* Um Carro é um ponteiro para uma struct carro */
typedef struct carro *Carro;
 
//INIT's
/* Cria um carro que pode receber um valor maximo de num_passageiros ao mesmo tempo*/
Carro carroInit(int numCarPassageiros);


//PRINTS's
/* Imprime as informações do carro*/
void carroPrint(Carro c);
 
#endif /* PASSAGEIRO_H_ */