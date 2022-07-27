#include <stdio.h>
#include <container.h>
#include <loadFilesCT.h>
#include <matrizAdjacente.h>
#include <genericPath.h>


void main(int argc, char const *argv[])
{
  srand(time(NULL));
  
  printf("\nArquivo %s\n", argv[1]);
  Container ct = loadPath(argv[1]);

  containerPrint(ct);

  for (int i = 0; i < 2; i++)
  {
    PathTS path = PathTSrandGuloso_int(ct->m);
    PathTSprint_int(path);
    free(path->path);
    free(path->value);
    free(path);
  }
  
  free(ct->m->nodeVal);
  free(ct->m);
  free(ct->p->destino);
  free(ct->p->origem);
  free(ct->p->valorMaximo);
  free(ct->p);
  free(ct->c->listPassageiro);
  free(ct->c);
  free(ct);
  
}

