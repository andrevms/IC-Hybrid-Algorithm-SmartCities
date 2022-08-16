#include <stdio.h>
#include <string.h>
#include <container.h>

#define IteractionsMultiStart 200
#define ParticleSwarmOp 20
#define IteractionsSwarmOp 10

void main(int argc, char *argv[])
{
  srand(time(NULL));
  
  for (size_t i = 1; i < argc; i = i + 2)
  {
    printf("\nArquivo %s\n", argv[i]);
    Container ct = loadPath(argv[i], IteractionsMultiStart, ParticleSwarmOp, IteractionsSwarmOp);
    run(ct, argv[i+1]);
    freeCTattributes(ct);
    printf("Finalizado\n");
  }
}

