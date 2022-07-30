#include <stdio.h>
#include <container.h>
#include <loadFilesCT.h>

#define INTERACTIONS 5

void main(int argc, char const *argv[])
{
  srand(time(NULL));
  
  printf("\nArquivo %s\n", argv[1]);
  Container ct = loadPath(argv[1]);

  //containerPrint(ct);


  printf("\n\nIniciando resultados\n\n");
  PathTS* pathList = calloc( INTERACTIONS, sizeof(*pathList));
  PathTS* path2optList = calloc( INTERACTIONS, sizeof(*pathList));
  Passageiros* passList = calloc ( INTERACTIONS, sizeof(*passList));

  for (int i = 0; i <  INTERACTIONS; i++)
  {
    pathList[i] = PathTSrandGuloso_int(ct->m);
    
    printf("\nInteraction %d\n", i);
    printf("\nRealizando PathTSrandGuloso %d\n", i);
    PathTSprint_int(pathList[i]);

    printf("Realizando o 2opt\nResultados\n");

    path2optList[i] = optimize2opt(pathList[i], ct->m);
    PathTSprint_int(path2optList[i]);

    printf("\nInserindo Passageiros 2opt\n");
    passList[i] = pListOnPath(ct->p, pathList[i], ct->c);
    passageiroPrint(passList[i]);

  }

  for (int i = 0; i < INTERACTIONS; i++)
  {
    free(pathList[i]->path);
    free(pathList[i]->value);
    free(pathList[i]);
    
    free(passList[i]->destino);
    free(passList[i]->origem);
    free(passList[i]->valorMaximo);
    free(passList[i]->valorPago);
    free(passList[i]);
  }
  
  free(pathList);
  free(passList);  
  
  free(ct->m->nodeVal);
  free(ct->m);
  free(ct->p->destino);
  free(ct->p->origem);
  free(ct->p->valorMaximo);
  free(ct->p->valorPago);
  free(ct->p);
  free(ct->c);
  free(ct);
  
}

