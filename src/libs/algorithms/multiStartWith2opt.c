#include <multiStartWith2opt.h>


void runMultiStartWith2opt(int numIteractions, Matriz m, ListPassageiros p, Car c, char filePath[]) {

    //Calcular tempo iniciando aqui
    struct timeval start, end;
    gettimeofday(&start, NULL);
 
    PathTS* pathsList = calloc(numIteractions, sizeof(PathTS));
    PathTS* auxPathList = calloc(numIteractions, sizeof(PathTS));

    //Gerando os Caminhos Aleatorios
    //Armazena o inicial e o optimizado
    for (size_t i = 0; i < numIteractions; i++){ 
        auxPathList[i] = generateRandGulosoPathTS_int(m);
        pathsList[i] =  optimize2opt(auxPathList[i], m);
    }

    //Inserindo passageiros nos Caminhos
    ListPassageiros* passageirosList = calloc(numIteractions, sizeof(ListPassageiros));
    for (size_t i = 0; i < numIteractions; i++){ 
        passageirosList[i] = boardPassengersOnPath(p, pathsList[i], c, m);  
        pathsList[i]->numPassengersOnPath = passageirosList[i]->listSize; 
    }

    //Finaliza o Calculo do tempo aqui
    gettimeofday(&end, NULL);
 
    //Encontra Melhor Caminho
    int indiceMelhorCaminho = 0;
    int valMelhorCaminho = *(((int*)pathsList[indiceMelhorCaminho]->totalValue));
    int numPassageirosMelhorCaminho = pathsList[indiceMelhorCaminho]->numPassengersOnPath;
    for (size_t i = 0; i < numIteractions; i++) { 
        int valCaminhoAtual = *(((int*)pathsList[i]->totalValue));
        int numPassageirosAtual = pathsList[i]->numPassengersOnPath;
        if (  (valMelhorCaminho > valCaminhoAtual && numPassageirosMelhorCaminho <= numPassageirosAtual) || 
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

    //Calcula o tempo de execução
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

   //Imprimir as media no file
    char* fileName = calloc(100, sizeof(char));
    strcpy(fileName, filePath);
    strcat(fileName, "multiStartWith2opt.txt");

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
    for (size_t i = 0; i < numIteractions; i++) {
        //printPathTSInFile_int(fileName, auxPathList[i], m, i); 
        printPathTSInFile_int(fileName, pathsList[i], m, i); 
    }

    //Desalloc
    for (size_t i = 0; i < numIteractions; i++) { 
        freePath(pathsList[i]); 
        freePath(auxPathList[i]);
        freeListPassengers(passageirosList[i]);
    }
    
    free(pathsList);
    free(auxPathList);
    free(passageirosList);
    free(fileName);
}

int* arrayRandGuloso_int(Matriz m){
    int mSizePlus1 = m->size_x +1;
    int mSizeMinus1 = m->size_x -1;
    
    //Preparando array auxiliar com tamanhos de [1, MatrizTamanho-1] (-1 pq inicia com 0)
    int* entradasPossiveis = calloc (mSizeMinus1, sizeof(int));
    for (size_t i = 0; i < mSizeMinus1; i++) {entradasPossiveis[i] = i+1;}

    //Preparando array PathRandom com tamanho [MatrizTamanho + 1] Pois é uma pathTS
    int* entradasPath = calloc (mSizePlus1, sizeof(int));
    entradasPath[0] = 0; //Primeira e ultima entrada sempre iguais (pathTS)
    entradasPath[m->size_x] = 0; 

    //Iniciando array para armazenar os pesos das entradas
    int* pesosEntradas = calloc (mSizeMinus1, sizeof(int)); 
    
    //Iniciar criação do path com random
    for (size_t i = 0; i < mSizeMinus1; i++)
    {
        //Atribuindo os pesos das entradas ao array pesosEntradas apenas com os pesos das EntradasPossiveis
        for (int j = 0; j < mSizeMinus1-i; j++)
        {
            int entradaAtual = entradasPath[i];
            int entradaDestino = entradasPossiveis[j];
            pesosEntradas[j] = getMatrizElementValue_int(m, entradaAtual, entradaDestino);
        }

        int pVal = sumArrayElements(pesosEntradas, mSizeMinus1-i);
        int vRand = rand()%pVal; //Valor randomizado dos pesos possiveis

        int indice = 0;
        do
        {
            //Condição de parada entre os pesos
            int breakAtual =  sumArrayElements(pesosEntradas, indice+1);
            if (vRand < breakAtual)
            {
               //printf("Entrou aqui indice no array %d, valor no array = %d, vRand = %d , breakAtual = %d\n", indice, entradasPossiveis[indice], vRand, breakAtual);
                
                int aux = entradasPossiveis[indice];
                entradasPath[i+1] = aux;

                if(indice != (mSizeMinus1-i)) {
                    entradasPossiveis[indice] = entradasPossiveis[(mSizeMinus1-i)-1];
                }
                break;
            }
            indice++;
        } while (indice < mSizeMinus1-i);
    }

    free(pesosEntradas);
    free(entradasPossiveis);
    return entradasPath;
}

PathTS generateRandGulosoPathTS_int(Matriz m) {
    int* pathResult = arrayRandGuloso_int(m);
     //Calculando custo do caminho

    int* valueCaminho = calloc(1, sizeof(int));
    valueCaminho[0] = 0;
    for (int i = 0; i < m->size_x; i++) {  
        int positBegin = pathResult[i];
        int positEnd = pathResult[i+1];
        valueCaminho[0] += getMatrizElementValue_int(m,positBegin, positEnd); 
    }
    //printf("Custo do caminho : %d\n", *valueCaminho);

    PathTS p = iPathTS_int(pathResult, valueCaminho, m->size_x+1); 
    return p;
}

/**/
PathTS optimize2opt(PathTS pTS, Matriz m) {
    PathTS oldPath = calloc (1, sizeof(*oldPath));
    
    //Evitar que o pTS que seja desalocado criando uma copia 
    
    //Armazena os valores do Path
    int* auxPath = calloc (pTS->pathSize, sizeof(int));
    for (size_t i = 0; i < pTS->pathSize; i++){ auxPath[i] = *(((int*)pTS->path)+i); }
    //Armazena o valor total do caminho
    int* auxTotalValuePath = calloc (1, sizeof(int));
    auxTotalValuePath[0] = *(((int*)pTS->totalValue));
    //Armazena o tamanho do auxPath
    int auxPathSize = pTS->pathSize;
    
    //Atribuindo as variaveis a um novo PathTS que sera utilizado no algoritmo
    oldPath->path = auxPath;
    oldPath->pathSize = auxPathSize;
    oldPath->totalValue = auxTotalValuePath;


    int mSize = m->size_x;
    int mSizePlus1 = m->size_x +1;
    int mSizeMinus1 = m->size_x -1;
    
    // Inicio do algoritmo
    int improvement = 0;
    do {
            improvement = 0;

            for (int i = 1; i < mSizePlus1; i++) {
                for (int j = i + 1; j < mSize; j++) {

                    //Nova rota
                    int* newRoute = swap2opt(oldPath, i, j);
                    //Valor do path
                    int* newRouteTotalValue = calloc(1, sizeof(int));
                    newRouteTotalValue[0] = calculePathValue(newRoute, mSizePlus1, m);

                    if(newRouteTotalValue[0] < *(((int*)oldPath->totalValue)) ){
                        //printf("\nEntrou aqui %d , old %d  ", newRouteValue , oldRouteValue);printf("\nnewRoute : ");for (size_t i = 0; i < 11; i++){printf("%d ", newRoute[i]);}printf("\nnewPesos : ");for (size_t i = 0; i < 10; i++){printf("%d ", newPesosRoute[i]);}printf("\n\n");
                    
                        free(oldPath->path);
                        free(oldPath->totalValue);
                        free(oldPath);
                        oldPath = iPathTS_int(newRoute, newRouteTotalValue, mSizePlus1);
                        improvement = 1;
                        break;
                    }

                    free(newRouteTotalValue);
                    free(newRoute);
                }
                if(improvement == 1){
                    break;
                }
            }
        } while(improvement == 1);

    return oldPath;
}

/*Will be used like generics*/
void* swap2opt(PathTS pTS, int swapBegin, int swapEnd) {
  /*
  TODO
  adicionar um quarto parametro com tipo da funçao e botar como if
  if(){
    return swap2opt_int
  }else if (){
    return swap2opt_float 
  }[...]
  */
  return swap2opt_int((int*)pTS->path, pTS->pathSize, swapBegin, swapEnd);
}

/**/
int* swap2opt_int(int* path, int pathSize, int swapBegin, int swapEnd){
    int* newRoute = calloc(pathSize, sizeof(int));
    
    //printf("Imprimindo newRoute %d %d: ", swapBegin, swapEnd);
    for (size_t i = 0; i < swapBegin; i++)
    {
        newRoute[i] = path[i];
    }
    for (size_t i = swapBegin, y = 0; i <= swapEnd; i++, y++)
    {
        newRoute[i] = path[swapEnd - y];
        //printf("s%d ", newRoute[i]);
    }

    for (size_t i = swapEnd+1; i < pathSize; i++)
    {
        newRoute[i] = path[i];
        //printf("%d ", newRoute[i]);
    }

    //printf("\n");
    return newRoute;
}
