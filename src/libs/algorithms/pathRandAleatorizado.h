#ifndef __PATHRANDALEATORIZADO_H_
#define __PATHRANDALEATORIZADO_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include <pathTS.h>
#include <passageiros.h>
#include <matrizAdjacente.h>


/* \brief 
 * \param 
 * \return
 */
void runPathRand(int numIteractions, Matriz m, ListPassageiros p, Car c, char filePath[]);

/* \brief 
 * \param 
 * \return 
 */
int* arrayRandAleatorio_int(Matriz m);

/* \brief 
 * \param 
 * \return 
 */ 
PathTS generateRandomPathTS_int(Matriz m);

PathTS generateRandomPathTSWithPassageiros_int(Matriz m, ListPassageiros p, Car c);

#endif /* PATHRANDALEATORIZADO_H_ */