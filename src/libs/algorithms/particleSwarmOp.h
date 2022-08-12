#ifndef __PARTICLESWARMOP_H_
#define __PARTICLESWARMOP_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h> 

#include <pathTS.h>
#include <passageiros.h>
#include <matrizAdjacente.h>
#include <pathRandAleatorizado.h>
#include <multiStartWith2opt.h>


/* \brief 
 * \param 
 * \return
 */
void runParticleSwarmOp(int numIteractions, int numParticles, Matriz m, ListPassageiros p, Car c, char filePath[]);

/* \brief 
 * \param 
 * \return 
 */ 
PathTS particleSwarmOp(int numParticles, Matriz m, ListPassageiros p, Car c);

int velocityP (float pr1, float pr2, float pr3);
PathTS pathRelinking ( PathTS pathChange, PathTS pathtarget, int pathSize, Matriz m, ListPassageiros p, Car c);
int searchBestPath(PathTS* pTSlist, int sizeList);

#endif /* PARTICLESWARMOP_H_ */