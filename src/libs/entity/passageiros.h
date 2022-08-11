#ifndef __PASSAGEIRO_H_
#define __PASSAGEIRO_H_
  
#include <stdlib.h>
#include <stdio.h>
#include <pathTS.h>
#include <carro.h>
#include <matrizAdjacente.h>

struct passageiros {
    int* origem;
    int* destino;
    float* valorMaximo;
    float* valorPago;
    int listSize;
};

/* ListPassageiros é um ponteiro para passageiros. */
typedef struct passageiros *ListPassageiros;
 
//INIT's

/*
 * \brief Init a List of passengers
 * \param entry Integer Pointer --> Array with the boarding node number of each passenger
 * \param out Integer Pointer --> Array with the destination node number of each passenger
 * \param value Float Pointer --> Array with the Max value possible payed for each passenger
 * \param payValue Float Pointer --> Array with the paid value of each passenger
 * \param size Integer --> Number of the size of the arrays (number of passengers)
 * \return return a Pointer to ListPassageiros
 *         return NULL IF not well initialized 
 * 
 * \info Object should be dealloc by user
 */
ListPassageiros initListPassageiros(int* entry, int* out, float* value, float* payValue, int size);

//FUNCTION's

/*
 * \brief Try to board a passengersList on a pathTS
 * \param passengersList ListPassageiros --> Pointer to struct passageiros [NOT NULL]
 * \param pathTS PathTS --> Pointer to a Travelling Salesman Path [NOT NULL]
 * \param car --> Pointer to a Car [NOT NULL]
 * \return return a Pointer to ListPassageiros
 *         return NULL IF not well initialized 
 * 
 * \info Object should be dealloc by user
 */
ListPassageiros boardPassengersOnPath(ListPassageiros passengersList, PathTS pathTS, Car car, Matriz m);

//PRINTS's

/*
 * \brief Write Passengers Informations to stdout
 * \param passengersList Passenger Pointer --> Passengers that will be printed
 */
void printListPassengers(ListPassageiros passengersList);


/*
 * \brief Write Passengers Informations on file
 *\param fileName --> Name of the file that will be write
 * \param passengersList Passenger Pointer --> Passengers that will be printed
 */
void printListPassengersInFile(const char fileName[], ListPassageiros passengersList);


void freeListPassengers(ListPassageiros p);
#endif /* PASSAGEIRO_H_ */