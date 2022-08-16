#include <particleSwarmOp.h>

#define MAXITERACTIONS 100
#define WITHOUTIMPROVEMENT 10


void runParticleSwarmOp(int numIteractions, int numParticles, Matriz m, ListPassageiros p, Car c, char filePath[]) {
    //Calcular tempo iniciando aqui
    struct timeval start, end;
    gettimeofday(&start, NULL);

    PathTS* gbestList = calloc(numIteractions, sizeof(PathTS));
    //Roda o algoritmo nuvem de particulas numIteractions vezes
    for (size_t i = 0; i < numIteractions; i++) { gbestList[i] = particleSwarmOp(numParticles, m, p, c);}

    // Calcular Tempo até aqui
    gettimeofday(&end, NULL);
    
    //Encontra Melhor Caminho
    int indiceMelhorCaminho = searchBestPath(gbestList, numIteractions);

    //Calculando a media dos caminhos
    float mediaCaminhos = 0;
    for (size_t i = 0; i < numIteractions; i++) { mediaCaminhos += *(((int*)gbestList[i]->totalValue));}
    mediaCaminhos = mediaCaminhos/numIteractions;
    
    //Calculando a media dos passageiros
    float mediaPassageiros = 0;
    for (size_t i = 0; i < numIteractions; i++) { mediaPassageiros += gbestList[i]->numPassengersOnPath;}
    mediaPassageiros = mediaPassageiros/numIteractions;

    //Calcula o tempo de execução
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    //Imprimir a media dos caminhos no file
    char* fileName = calloc(100, sizeof(char));
    strcpy(fileName, filePath);
    strcat(fileName, "particleSwarmOp.txt");

    FILE *fp;
    if ( (fp= fopen(fileName, "w+") ) != NULL) {
        fprintf(fp, "Tempo de execução em segundos %lds\nTempo de execução em microsegundos %ld\n", seconds, micros);
        fprintf(fp, "Valor Medio dos caminho : %f\n", mediaCaminhos);
        fprintf(fp, "Valor Medio dos embarcados passageiros : %f\n\n", mediaPassageiros);
        fprintf(fp, "Melhor caminho: ");
        fclose(fp); 
    }

    //Imprimindo melhor caminho
    printPathTSInFile_int(fileName, gbestList[indiceMelhorCaminho], m, indiceMelhorCaminho);
    //Imprimindo caminhos on file
    for (size_t i = 0; i < numIteractions; i++) {
        printPathTSInFile_int(fileName, gbestList[i], m, i); 
    }

    //Desalloc
    for (size_t i = 0; i < numIteractions; i++) { 
        freePath(gbestList[i]);
    }
    free(gbestList);
    free(fileName);
}

PathTS particleSwarmOp(int numParticles, Matriz m, ListPassageiros p, Car c) {
    
    //Criando particulas totalmente randomizadas
    PathTS* particlesPathList = calloc(numParticles, sizeof(PathTS*));
    for (size_t i = 0; i < numParticles; i++){ particlesPathList[i] = generateRandomPathTSWithPassageiros_int(m, p, c); }

    //init pbest com copias das particulas
    PathTS* pBestPathList = calloc(numParticles, sizeof(PathTS*));
    for (size_t i = 0; i < numParticles; i++){ pBestPathList[i] = copyPath(particlesPathList[i]); }
    
    //Procura melhor caminho
    int indiceMelhorCaminho = searchBestPath(pBestPathList, numParticles);
    PathTS gBest = copyPath(pBestPathList[indiceMelhorCaminho]);

    //Iniciando Velocidades
    float pr1 = 0.900;
    float pr2 = 0.050;
    float pr3 = 0.050;
    //Condições de parada
    int numNoImproviment = 0;
    int hasImproviment = 0;
    int numIteraction = 0;

    //Inicia algoritmo
    do
    {   
        //Atualiza pbest e gbest
        for (size_t i = 0; i < numParticles; i++) {
            //Particula atual
            int valParticula = *(((int*)particlesPathList[i]->totalValue));
            int numPassageirosParticula = particlesPathList[i]->numPassengersOnPath;
            //pBest da particula
            int valpbest = *(((int*)pBestPathList[i]->totalValue));
            int numPassageirospbest = pBestPathList[i]->numPassengersOnPath;
            //gBest 
            int valgbest = *(((int*)gBest->totalValue));
            int numPassageirosgbest = gBest->numPassengersOnPath;
            
            //Testa se houve melhora no pBest[i]
            if( (valParticula < valgbest && numPassageirosParticula >= numPassageirosgbest )|| 
            (valParticula <= valpbest && numPassageirosParticula > numPassageirospbest) ) {
                //fprintf(stdout, "Atualiza pBest[%d]\n", i);

                PathTS aux = copyPath(particlesPathList[i]);
                free(pBestPathList[i]->path);
                free(pBestPathList[i]->totalValue);

                pBestPathList[i]->path = aux->path;
                pBestPathList[i]->totalValue = aux->totalValue;
                pBestPathList[i]->numPassengersOnPath = aux->numPassengersOnPath;

                free(aux);

            }

            //Testa se houve melhora no gBest
            if( (valParticula < valgbest && numPassageirosParticula >= numPassageirosgbest ) || 
            (valParticula <= valgbest && numPassageirosParticula > numPassageirosgbest) ) {
                //fprintf(stdout, "Atualiza gbest com [%d]\n", i);

                PathTS aux = copyPath(particlesPathList[i]);
                free(gBest->path);
                free(gBest->totalValue);

                gBest->path = aux->path;
                gBest->totalValue = aux->totalValue;
                gBest->numPassengersOnPath = aux->numPassengersOnPath;

                free(aux);

                hasImproviment++;
            }
        }

        //Atualiza particulas
        for (size_t i = 0; i < numParticles; i++) {
            //Calcula Velocidade
            int velocidade = rand()%100;
            //fprintf(stdout, "velocidade %d\n",velocidade);
            PathTS aux;
            if(velocidade < pr1*100) {
                aux = optimize2optWithPassageiros_int(particlesPathList[i], m, p, c);
                //aux = pathRelinking (particlesPathList[i], particlesPathList[i], particlesPathList[i]->pathSize, m, p, c);
                //fprintf(stdout, "entrou em particles\n");
            }else if ( velocidade < (pr1+pr2)*100){
                //fprintf(stdout, "entrou em pbest\n");
                aux = pathRelinking (particlesPathList[i], pBestPathList[i], particlesPathList[i]->pathSize, m, p, c);
            }else {
                //fprintf(stdout, "entrou em gbest\n");
                aux = pathRelinking (particlesPathList[i], gBest, particlesPathList[i]->pathSize, m, p, c);

            }
            
            free(particlesPathList[i]->path);
            free(particlesPathList[i]->totalValue);

            particlesPathList[i]->path = aux->path;
            particlesPathList[i]->totalValue = aux->totalValue;
            particlesPathList[i]->numPassengersOnPath = aux->numPassengersOnPath;

            free(aux);
        }

        //Atualiza as velocidades
        pr1= pr1*0.95;
        pr2= pr2*1.01;
        pr3= 1-(pr1+pr2);
        //Atualizando numero de interação
        numIteraction++;

        //Atualiza contador de melhorias se houver
        (hasImproviment == 0) ? numNoImproviment++ : (numNoImproviment = 0);
        hasImproviment = 0;
    } while (numIteraction < MAXITERACTIONS && numNoImproviment < WITHOUTIMPROVEMENT);
    
    //Desalloc
    for (size_t i = 0; i < numParticles; i++) { 
        freePath(particlesPathList[i]);
        freePath(pBestPathList[i]);
    }
    free(particlesPathList);
    free(pBestPathList);

    return gBest;
}

int searchBestPath(PathTS* pTSlist, int sizeList) {
    int indiceMelhorCaminho = 0;
    int valMelhorCaminho = *(((int*)pTSlist[indiceMelhorCaminho]->totalValue));
    int numPassageirosMelhorCaminho = pTSlist[indiceMelhorCaminho]->numPassengersOnPath;
    for (size_t i = 0; i < sizeList; i++)
    {   
        int valCaminhoAtual = *(((int*)pTSlist[i]->totalValue));
        int numPassageirosAtual = pTSlist[i]->numPassengersOnPath;
        if ( (valMelhorCaminho > valCaminhoAtual && numPassageirosMelhorCaminho <= numPassageirosAtual) || 
            (valMelhorCaminho >= valCaminhoAtual && numPassageirosMelhorCaminho < numPassageirosAtual) ) {
            indiceMelhorCaminho = i;
            valMelhorCaminho = valCaminhoAtual;
            numPassageirosMelhorCaminho = numPassageirosAtual;
        }
    }
    return indiceMelhorCaminho;
}

int velocityP (float pr1, float pr2, float pr3) {
    
}


PathTS pathRelinking ( PathTS pathChange, PathTS pathtarget, int pathSize, Matriz m, ListPassageiros p, Car c) {

    
   //Armazena o tamanho do auxPath
   int auxPathSize = pathChange->pathSize;
   //Armazena os valores do Path
    int* auxPath = calloc (auxPathSize, sizeof(int));
    for (size_t i = 0; i < auxPathSize; i++) { auxPath[i] = *(((int*)pathChange->path)+i);}

    int indiceChange = -1;
    int indiceTarget = -1;
    int breakCond = 0;

    for (size_t i = 1; i < auxPathSize-1; i++)
    {
        for (size_t j = 1; j < auxPathSize-1; j++)
        {
            if(auxPath[i] == *(((int*)pathtarget->path)+j) && i != j){
                indiceChange = i;
                indiceTarget = j;
                breakCond = 1;
                break;
            }
        }   
        if (breakCond == 1){break;}
    }
     
    if (breakCond == 1)
    {
        int aux = auxPath[indiceChange];
        auxPath[indiceChange] = *(((int*)pathChange->path)+indiceTarget);
        auxPath[indiceTarget] = aux;
    }
    
    //Armazena o valor total do caminho
    int* auxTotalValuePath = calloc (1, sizeof(int));
    auxTotalValuePath[0] = calculePathValue(auxPath, auxPathSize, m);
    
    //Armazena o numero de passageiros

    ListPassageiros passageirosList = boardPassengers(p, auxPath, c, m);
    int auxNumPassageiros = passageirosList->listSize;

    freeListPassengers(passageirosList);

   return initPathTS_int(auxPath, auxTotalValuePath, auxPathSize, auxNumPassageiros);
}

//P updatePath(pathTS particle, PathTS pbest, PathTS gbest, int velocidade );*/