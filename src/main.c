#include <stdio.h>
#include <container.h>

#define INTERACTIONS 50

void main(int argc, char const *argv[])
{
  srand(time(NULL));
  
  for (size_t i = 1; i < argc; i++)
  {
    printf("\nArquivo %s\n", argv[i]);
    Container ct = loadPath(argv[i], INTERACTIONS);
    printf("Iniciando algoritmo\n");
    run(ct);
    
    containerPrint(ct);
    printf("Desalocando memoria\n");
    freeCTattributes(ct);
    printf("Finalizado\n");
  }
}

