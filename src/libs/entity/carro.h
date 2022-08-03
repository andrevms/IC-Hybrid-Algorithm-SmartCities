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

/*
 * \brief Inicializa um carro
 * \param numCarPassageiros Integer Number of passengers that the car can take.
 * \return A Pointer for an object Carro with numMaxPassageiros with the number received.
 *         NULL if parameters less then 0.
 * \info Object should be desaloc by user
 */
Carro carroInit(int numCarPassageiros);

//PRINTS's
/*
 * \brief Print's car Informations
 * \param car Pointer to a carro that will be printed
 * 
 * \info IF car NULL, will print an error message 
 */
void carroPrint(Carro car);
 
#endif /* PASSAGEIRO_H_ */