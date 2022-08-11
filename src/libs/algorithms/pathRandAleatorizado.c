#include <pathRandAleatorizado.h>

void runPathRand( int numIteractions, Matriz m, ListPassageiros p, Car c, char filePath[]) {
    //Calcular tempo iniciando aqui
    struct timeval start, end;
    gettimeofday(&start, NULL);
 
    //Inicialização da variavel com todos os paths gerados
    PathTS* pathsList = calloc(numIteractions, sizeof(PathTS));
    //Gerando os Caminhos Aleatorios
    for (size_t i = 0; i < numIteractions; i++){ pathsList[i] = generateRandomPathTS_int(m); }
    
    //Inserindo passageiros nos Caminhos
    ListPassageiros* passageirosList = calloc(numIteractions, sizeof(PathTS));
    for (size_t i = 0; i < numIteractions; i++){ 
        passageirosList[i] = boardPassengersOnPath(p, pathsList[i], c, m);  
        pathsList[i]->numPassengersOnPath = passageirosList[i]->listSize; 
    }
    
    // Calcular Tempo até aqui
    gettimeofday(&end, NULL);

    //Encontra Melhor Caminho
    int indiceMelhorCaminho = 0;
    int valMelhorCaminho = *(((int*)pathsList[indiceMelhorCaminho]->totalValue));
    int numPassageirosMelhorCaminho = pathsList[indiceMelhorCaminho]->numPassengersOnPath;
    for (size_t i = 0; i < numIteractions; i++) { 
        int valCaminhoAtual = *(((int*)pathsList[i]->totalValue));
        int numPassageirosAtual = pathsList[i]->numPassengersOnPath;

        if ( (valMelhorCaminho > valCaminhoAtual && numPassageirosMelhorCaminho <= numPassageirosAtual) || 
            (valMelhorCaminho >= valCaminhoAtual && numPassageirosMelhorCaminho < numPassageirosAtual) ) {
            indiceMelhorCaminho = i;
            valMelhorCaminho = valCaminhoAtual;
            numPassageirosMelhorCaminho = numPassageirosAtual;
        }
    }

    //Calculando a media dos caminhos
    float mediaCaminhos = 0;
    for (size_t i = 0; i < numIteractions; i++) { mediaCaminhos += *(((int*)pathsList[i]->totalValue));}
    mediaCaminhos = mediaCaminhos/numIteractions;

    //Calculando a media dos passageiros
    float mediaPassageiros = 0;
    for (size_t i = 0; i < numIteractions; i++) { mediaPassageiros += pathsList[i]->numPassengersOnPath;}
    mediaPassageiros = mediaPassageiros/numIteractions;

    //Calculando o tempo
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    //Criando o nome do arquivo
    char* fileName = calloc(100, sizeof(char));
    strcpy(fileName, filePath);
    strcat(fileName, "randAleatorio.txt");

    //Imprimir as medias e tempo no file
    FILE *fp;
    if ( (fp= fopen(fileName, "w+") ) != NULL) {
        fprintf(fp, "Tempo de execução em segundos %lds\nTempo de execução em microsegundos %ld\n", seconds, micros);
        fprintf(fp, "Valor Medio dos caminho : %f\n", mediaCaminhos);
        fprintf(fp, "Valor Medio dos embarcados passageiros : %f\n\n", mediaPassageiros);
        fprintf(fp, "Melhor caminho: ");
        fclose(fp); 
    }

    //Imprimindo melhor caminho
    printPathTSInFile_int(fileName, pathsList[indiceMelhorCaminho], m, indiceMelhorCaminho);

    //Imprimindo caminhos on file
    for (size_t i = 0; i < numIteractions; i++) { printPathTSInFile_int(fileName, pathsList[i], m, i); }

    //Desalloc
    for (size_t i = 0; i < numIteractions; i++) { 
        freePath(pathsList[i]);
        freeListPassengers(passageirosList[i]);
    }
    free(pathsList);
    free(passageirosList);
    free(fileName);
}

int* arrayRandAleatorio_int(Matriz m) {
    int mSizePlus1 = m->size_x +1;
    int mSizeMinus1 = m->size_x -1;
    
    //Preparando array auxiliar com tamanhos de [1, MatrizTamanho-1] (-1 pq inicia com 0)
    int* entradasPossiveis = calloc (mSizeMinus1, sizeof(int));
    for (size_t i = 0; i < mSizeMinus1; i++) {entradasPossiveis[i] = i+1;}

    //Preparando array PathRandom com tamanho [MatrizTamanho + 1] Pois é uma pathTS
    int* entradasPath = calloc (mSizePlus1, sizeof(int));
    entradasPath[0] = 0; //Primeira e ultima entrada sempre iguais (pathTS)
    entradasPath[m->size_x] = 0; 

    
    //Iniciar criação do path com random
    
    for (size_t i = 0; i < mSizeMinus1; i++) {
        //Sempre decrementa o mSizeMinus1 do array que estamos rodando
        int posicao = rand()%(mSizeMinus1-i);

        int aux = entradasPossiveis[posicao];
        entradasPath[i+1] = aux;
        
        //Se a posição escolhida não é a ultima do array, pegamos a posição escolhida e trocamos com o ultimo valor
        //para evitar repetições (o rand posição ja diminui o mSizeMinus1 a cada interação do for)
        if(posicao != (mSizeMinus1-i)-1) {
            entradasPossiveis[posicao] = entradasPossiveis[(mSizeMinus1-i)-1];
            entradasPossiveis[(mSizeMinus1-i)-1] = aux;
        }
    }

    /*
    //Testes
        for (size_t i = 0; i < mSizePlus1; i++) {fprintf(stdout, "%d ", entradasPath[i] );}
        fprintf(stdout, "\n");
    */
    free(entradasPossiveis);
    return entradasPath;
}

PathTS generateRandomPathTS_int(Matriz m) {

    int* arrayRand = arrayRandAleatorio_int(m);
    int * arrayTotalVal = calloc(1,sizeof(int));

    for (int i = 0; i < m->size_x; i++) {  
        int positBegin = arrayRand[i];
        int positEnd = arrayRand[i+1];
        arrayTotalVal[0] += getMatrizElementValue_int(m,positBegin, positEnd);
    }


    /* //Visualização dos valores 
        for (int i = 0; i < m->size_x; i++) {  
            int positBegin = arrayRand[i];
            int positEnd = arrayRand[i+1];
            fprintf(stdout, "%d ", getMatrizElementValue_int(m,positBegin, positEnd));
        }
        fprintf(stdout, "\n");
        fprintf(stdout, "%d\n", arrayTotalVal[0]);
    */

   PathTS p = iPathTS_int (arrayRand, arrayTotalVal, m->size_x+1);
   return p;
}

