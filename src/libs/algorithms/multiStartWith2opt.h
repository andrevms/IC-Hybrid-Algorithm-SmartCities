#ifndef _MULTISTARTWITH2OPT_H_
#define __MULTISTARTWITH2OPT_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <pathTS.h>
#include <passageiros.h>
#include <matrizAdjacente.h>

 

void runMultiStartWith2opt(int numIteractions, Matriz m, ListPassageiros p, Car c, char filePath[]);

//retorna um array com o caminho selecionado de forma aleatoria e gulosa utilizando os pesos das entradas para selecionar o caminho 
/*
 * \brief 
 * \param 
 * \param 
 * \param 
 * \return 
 * 
 * \info Object should be dealloc by user
 */
int* arrayRandGuloso_int(Matriz m);

/* \brief Retorna um caminho Guloso randomizado
 * \param m --> Matriz pointer with node values 
 * \return Um PathTS com o caminho Guloso randomizado por pesos
 */
PathTS generateRandGulosoPathTS_int(Matriz m);


PathTS optimize2opt(PathTS pTS, Matriz m);
void* swap2opt(PathTS pTS, int swapBegin, int swapEnd);
int* swap2opt_int(int* path, int pathSize, int swapBegin, int swapEnd);

#endif /* MULTISTARTWITH2OPT_H_ */