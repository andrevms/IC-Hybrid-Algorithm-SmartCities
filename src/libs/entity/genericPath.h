#ifndef __CAMINHO_H_
#define __CAMINHO_H_
  
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <matrizAdjacente.h>

struct travellingSalesmanPath {
    void* path;
    void* value;
    int pathSize;
};

/* Um PathTS é um ponteiro para uma travellingSalesmanPath*/
typedef struct travellingSalesmanPath *PathTS;
 
//INIT's
PathTS PathTSinit_int(int* pathCaminho, int* valuePath, int pathTamanho);

//FUNCTIONS
//Retorna um caminho randomizado aleatorio
PathTS PathTSrandom_int(Matriz m);

//Retorna um caminho aleatorio guloso com
PathTS PathTSrandGuloso_int(Matriz m);


//PRINTS's
void PathTSprint_int(PathTS p);
 
#endif /* CAMINHO_H_ */