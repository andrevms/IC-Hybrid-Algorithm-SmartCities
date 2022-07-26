#include <loadFilesCT.h>

Container loadPath(const char fileName[]) {

    FILE *fp;

    int matrizSize, numPassageiros, numCarPassageiros;
    int* vetorMatriz;
    int* pOrigem;
    int* pDestino;
    float* maxVal;

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
    Passageiros listPassageiros = pListInit(pOrigem, pDestino, maxVal, numPassageiros);
    Carro carro = carroInit(numCarPassageiros);

    Container ct = containerInit(matriz , listPassageiros, carro);


    printf("Arquivos loaded\n");
    return ct;
}