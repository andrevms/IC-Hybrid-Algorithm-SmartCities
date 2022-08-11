#ifndef __CONTAINER_H_
#define __CONTAINER_H_
  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <matrizAdjacente.h>
#include <passageiros.h>
#include <carro.h>
#include <pathTS.h>
#include <multiStartWith2opt.h>
#include <pathRandAleatorizado.h>
#include <particleSwarmOp.h>

struct container {
    Matriz m;
    ListPassageiros p;
    Car c;
    int numIteractionsMultiStart; 
    int numParticleSwarmOp;
    int numIteractionsSwarmOp;
};

/* Um Container é um ponteiro para o struct container, que armazena uma matriz m, uma quantidade de passageiros p e um veiculo c */
typedef struct container *Container;
 
//INIT's

/*
 * \brief Cria um container inicializado com os parametros recebidos
 * \param matriz Matriz --> Matriz Pointer com a matriz adjacente do problema [NOT NULL]
 * \param pList --> ListPassageiros Pointer com uma lista de passageiros [NOT NULL]
 * \param carro --> Car Pointer com o carro que sera utilizado
 * \param numIteractionsMultiStart --> Integer with the numbers of iteractions for MStart2opt.
 * \param numParticleSwarmOp --> Integer with the numbers of particles for ParticleSwarmOp.
 * \param numIteractionsSwarmOp --> Integer with the numbers of iteractions for ParticleSwarmOp.
 * \return A Pointer for a Container object with all params initialized.
 * \info Object should be dealloc with function --> freeCTattributes
 */
Container containerInit(Matriz matriz,
                    ListPassageiros pList,
                    Car carro, 
                    int numIteractionsMultiStart,
                    int numParticleSwarmOp,
                    int numIteractionsSwarmOp);

//Load Files

/*
 * \brief Init a container with info from a formatted file
 * \param fileName --> String com path do arquivo para leitura
 * \param numIteractionsMultiStart --> Integer with the numbers of iteractions for MStart2opt.
 * \param numParticleSwarmOp --> Integer with the numbers of particles for ParticleSwarmOp.
 * \param numIteractionsSwarmOp --> Integer with the numbers of iteractions for ParticleSwarmOp.
 * \return A Container initialized with matriz, listPassageiros and Car from file 
 * \info Object should be dealloc with function --> freeCTattributes
 */
Container loadPath(const char fileName[],
                int numIteractionsMultiStart,
                int numParticleSwarmOp,
                int numIteractionsSwarmOp);

//Run
/*
 * \brief 
 * \param
 */
void run(Container ct, char filePath[]);

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
void printContainer(Container ct);


/* Imprime as informações do contanier em arquivo*/
/*
 * \brief 
 * \param 
 */
void printContainerInFile(const char fileName[], Container ct);

#endif /* PASSAGEIRO_H_ */