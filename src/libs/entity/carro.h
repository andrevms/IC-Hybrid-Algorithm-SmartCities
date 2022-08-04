#ifndef __CARRO_H_
#define __CARRO_H_
  
#include <stdlib.h>
#include <stdio.h>

struct carro {
    int numMaxPassageiros;
};

/* Um Car é um ponteiro para uma struct carro */
typedef struct carro *Car;
 
//INIT's

/*
 * \brief Inicializa um carro com numero de passageiros
 * \param numCarPassageiros Integer Number of passengers that the car can take.
 * \return A Pointer for an object Car with numMaxPassageiros with the number received.
 *         NULL if parameters less then 0.
 * \info Object should be dealloc by user
 */
Car initCarWithVal(int numCarPassageiros);

//PRINTS's
/*
 * \brief Write Car Informations to stdout
 * \param car --> Pointer to a car that is going to be printed
 * 
 * \info IF car NULL, will print an error message 
 */
void printCar(Car car);
 
#endif /* PASSAGEIRO_H_ */