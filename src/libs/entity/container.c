#include <container.h>

Container containerInit( Matriz matriz, 
                        ListPassageiros pList, 
                        Car carro, 
                        int numIteractionsMultiStart, 
                        int numParticleSwarmOp, 
                        int numIteractionsSwarmOp) {
    Container ct = calloc ( 1, sizeof(*ct));
    ct->m = matriz;
    ct->p = pList;
    ct->c = carro;
    ct->numIteractionsMultiStart = numIteractionsMultiStart;
    ct->numParticleSwarmOp = numParticleSwarmOp;
    ct->numIteractionsSwarmOp = numIteractionsSwarmOp;
    return ct;
}

/**/
Container loadPath(const char fileName[], int numIteractionsMultiStart, int numParticleSwarmOp, int numIteractionsSwarmOp) {

    FILE *fp;

    int matrizSize, numPassageiros, numCarPassageiros;
    int* vetorMatriz;
    int* pOrigem;
    int* pDestino;
    float* maxVal;
    float* payVal;
    

    // Inicio da leitura do arquivo.
    if ((fp=fopen (fileName, "r")) != NULL) {
        printf("Arquivo encontrado\nIniciando Loading \n");

        //Leitura dos Valores : Tamanho da matriz, numero de passageiros e numero maximo de passageiros no carro;
        fscanf(fp, "%d %d %d\n", &matrizSize, &numPassageiros, &numCarPassageiros);
        
        //Alocação de vetor com tamanho da matriz [matrizSize * matrizSize]
        vetorMatriz = calloc ( (matrizSize * matrizSize), sizeof(int));
    
        //Leitura dos valores da matriz adjacente
        for (size_t i = 0; i < (matrizSize * matrizSize); i++)
        {
            fscanf(fp, "%d ", &vetorMatriz[i]);
        }

        fscanf(fp, "\n");
        
        pOrigem = calloc (numPassageiros, sizeof(int));
        pDestino = calloc (numPassageiros, sizeof(int));
        maxVal = calloc (numPassageiros, sizeof(float));
        payVal = calloc (numPassageiros, sizeof(float));

        for (size_t i = 0; i < numPassageiros; i++)
        {
            fscanf(fp, "%f %d %d", &maxVal[i], &pOrigem[i], &pDestino[i]);
        }

        fclose(fp);
    }

    //Testes
    //for (int i = 0; i < numPassageiros; i++){ 
    //        printf("passageiro[%d] %d %d %f\n", i, pOrigem[i],pDestino[i], maxVal[i]);
    //}

    //Inicia a matriz adjacente lida
    Matriz matriz = initMatrizWithArray_int(matrizSize, matrizSize, vetorMatriz);
    ListPassageiros listPassageiros = initListPassageiros(pOrigem, pDestino, maxVal, payVal, numPassageiros);
    Car carro = initCarWithVal(numCarPassageiros);

    Container ct = containerInit(matriz , listPassageiros, carro, numIteractionsMultiStart, numParticleSwarmOp, numIteractionsSwarmOp);
    return ct;
}

void run(Container ct, char filePath[]) {
  runPathRand(ct->numIteractionsMultiStart, ct->m, ct->p, ct->c, filePath);
  runMultiStartWith2opt(ct->numIteractionsMultiStart, ct->m, ct->p, ct->c, filePath);
  runGRASPwith2opt(ct->numIteractionsMultiStart, ct->m, ct->p, ct->c, filePath);
  runParticleSwarmOp(ct->numIteractionsSwarmOp, ct->numParticleSwarmOp, ct->m, ct->p, ct->c, filePath);
}


/**/
void freeCTattributes(Container ct) {
  freeMatriz(ct->m);
  freeListPassengers(ct->p);
  free(ct->c);
  free(ct);
}

/**/
void printContainer(Container ct){
  printMatriz_int(ct->m);
  printListPassengers(ct->p);
  printCar(ct->c);
}

/**/
void printContainerInFile(const char fileName[], Container ct) {
  FILE *fp;

  printCarInFile(fileName, ct->c);
  printMatrizInFile_int(fileName, ct->m);
  printListPassengersInFile(fileName, ct->p);
}