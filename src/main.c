#include <stdio.h>
#include <container.h>
#include <loadFilesCT.h>
#include <matrizAdjacente.h>
#include <genericPath.h>


void main(int argc, char const *argv[])
{

  printf("\nArquivo %s\n", argv[1]);
  Container ct = loadPath(argv[1]);


  MATRIZprint_int(ct->m);
  passageiroPrint(ct->p);
  carroPrint(ct->c);

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

