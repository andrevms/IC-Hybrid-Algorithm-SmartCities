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
    ListPassageiros p;
    Car c;
    int interactions;
    PathTS* pathList;
    ListPassageiros* passList;
    PathTS* path2optList;
    ListPassageiros* pass2optList;

};

/* Um Container é um ponteiro para o struct container, que armazena uma matriz m, uma quantidade de passageiros p e um veiculo c */
typedef struct container *Container;
 
//INIT's

/*
 * \brief Cria um container
 * \param matriz Matriz --> Matriz Pointer com a matriz adjacente do problema [NOT NULL]
 * \param pList --> ListPassageiros Pointer com uma lista de passageiros [NOT NULL]
 * \param carro --> Car Pointer com o carro que sera utilizado
 * \param interactions --> Integer with the numbers of particles that we need.
 * \return A Pointer for a Container object with all params initialized.
 * \info Object should be dealloc with function --> freeCTattributes
 */
Container containerInit(Matriz matriz, ListPassageiros pList, Car carro, int interactions);

//Load Files

/*
 * \brief 
 * \param 
 * \return 
 * \info Object should be dealloc with function --> freeCTattributes
 */
Container loadPath(const char fileName[], int interactions);

//Run
/*
 * \brief 
 * \param
 */
void run(Container ct);

//Free
/*
 * \brief 
 * \param 
 * \return 
 * \info Object from param is dealloc in the function
 */
void freeCTattributes(Container ct);

//PRINTS's

/* Imprime as informações do contanier*/
/*
 * \brief 
 * \param 
 */
void containerPrint(Container ct);

#endif /* PASSAGEIRO_H_ */