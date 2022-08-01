#include <container.h>

Container containerInit( Matriz matriz, Passageiros pList, Carro carro, int interactions){
    Container ct = calloc ( 1, sizeof(*ct));
    ct->m = matriz;
    ct->p = pList;
    ct->c = carro;
    ct->interactions = interactions;
    ct->pathList = calloc( interactions, sizeof(*ct->pathList));
    ct->passList = calloc( interactions, sizeof(*ct->passList));
    ct->path2optList = calloc( interactions, sizeof(*ct->path2optList));
    ct->pass2optList = calloc( interactions, sizeof(*ct->pass2optList));
    return ct;
}

void containerPrint(Container ct){
  MATRIZprint_int(ct->m);
  passageiroPrint(ct->p);
  carroPrint(ct->c);

  for (int i = 0; i <  ct->interactions; i++)
  {

    printf("\nInteraction %d\n", i);
    printf("\nPathTSrandGuloso %d\n", i);
    PathTSprint_int(ct->pathList[i]);
    printf("\nPassageiros\n");
    passageiroPrint(ct->passList[i]);

    printf("\nResultados 2opt\n");
    PathTSprint_int(ct->path2optList[i]);
    printf("\nPassageiros 2opt\n");
    passageiroPrint(ct->pass2optList[i]);
  }
}

void run(Container ct){
  for (int i = 0; i <  ct->interactions; i++)
  {
    ct->pathList[i] = PathTSrandGuloso_int(ct->m);
    ct->passList[i] = pListOnPath(ct->p, ct->pathList[i], ct->c);
    ct->path2optList[i] = optimize2opt(ct->pathList[i], ct->m);
    ct->pass2optList[i] = pListOnPath(ct->p, ct->path2optList[i], ct->c);
  }
}


void freeCTattributes(Container ct) {
  for (int i = 0; i < ct->interactions; i++)
  {
    free(ct->pathList[i]->value);
    free(ct->pathList[i]->path);
    free(ct->pathList[i]);

    free(ct->path2optList[i]->path);
    free(ct->path2optList[i]->value);
    free(ct->path2optList[i]);
    
    free(ct->pass2optList[i]->destino);
    free(ct->pass2optList[i]->origem);
    free(ct->pass2optList[i]->valorMaximo);
    free(ct->pass2optList[i]->valorPago);
    free(ct->pass2optList[i]);

    free(ct->passList[i]->destino);
    free(ct->passList[i]->origem);
    free(ct->passList[i]->valorMaximo);
    free(ct->passList[i]->valorPago);
    free(ct->passList[i]);
  }
  
  free(ct->pathList);
  free(ct->passList);
  free(ct->pass2optList);
  free(ct->path2optList);
  
  free(ct->m->nodeVal);
  free(ct->m);
  free(ct->p->destino);
  free(ct->p->origem);
  free(ct->p->valorMaximo);
  free(ct->p->valorPago);
  free(ct->p);
  free(ct->c);

}

Container loadPath(const char fileName[], int interactions) {

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
    Matriz matriz = MATRIZinit_int(matrizSize, matrizSize, vetorMatriz);
    Passageiros listPassageiros = pListInit(pOrigem, pDestino, maxVal, payVal, numPassageiros);
    Carro carro = carroInit(numCarPassageiros);

    Container ct = containerInit(matriz , listPassageiros, carro, interactions);


    printf("Arquivos loaded\n");
    return ct;
}