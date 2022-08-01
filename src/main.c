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
  Passageiros* passList = calloc ( INTERACTIONS, sizeof(*passList));

  PathTS* path2optList = calloc( INTERACTIONS, sizeof(*pathList));
  Passageiros* passList2opt = calloc ( INTERACTIONS, sizeof(*passList2opt));

  for (int i = 0; i <  INTERACTIONS; i++)
  {
    pathList[i] = PathTSrandGuloso_int(ct->m);
    
    printf("\nInteraction %d\n", i);
    printf("\nRealizando PathTSrandGuloso %d\n", i);
    PathTSprint_int(pathList[i]);
    printf("\nInserindo Passageiros\n");
    passList[i] = pListOnPath(ct->p, pathList[i], ct->c);
    passageiroPrint(passList[i]);

    printf("\nRealizando o 2opt\nResultados\n");

    path2optList[i] = optimize2opt(pathList[i], ct->m);
    PathTSprint_int(path2optList[i]);

    printf("\nInserindo Passageiros 2opt\n");
    passList2opt[i] = pListOnPath(ct->p, path2optList[i], ct->c);
    passageiroPrint(passList2opt[i]);

  }

  for (int i = 0; i < INTERACTIONS; i++)
  {
    free(pathList[i]);

    free(path2optList[i]->path);
    free(path2optList[i]->value);
    free(path2optList[i]);
    
    free(passList2opt[i]->destino);
    free(passList2opt[i]->origem);
    free(passList2opt[i]->valorMaximo);
    free(passList2opt[i]->valorPago);
    free(passList2opt[i]);

    free(passList[i]->destino);
    free(passList[i]->origem);
    free(passList[i]->valorMaximo);
    free(passList[i]->valorPago);
    free(passList[i]);
  }
  
  free(pathList);
  free(passList);
  free(passList2opt);
  free(path2optList);
  
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

