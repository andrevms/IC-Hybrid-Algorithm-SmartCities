#include <pathTS.h>

//INIT
PathTS PathTSinit_int(int* pathCaminho, int* valuePath, int pathTamanho) {
    PathTS p = calloc (1,sizeof(*p));
    p->path = pathCaminho;
    p->value = valuePath;
    p->pathSize = pathTamanho;

    return p;
}

//FUNCTIONS

int* swap2opt(PathTS pTS, int swapBegin, int swapEnd) {
   int* newRoute = calloc(pTS->pathSize, sizeof(int));
    
    //printf("Imprimindo newRoute %d %d: ", swapBegin, swapEnd);
    for (size_t i = 0; i < swapBegin; i++)
    {
        newRoute[i] = *((int*)pTS->path + i);
        //printf("%d ", newRoute[i]);
    }
    for (size_t i = swapBegin, y = 0; i <= swapEnd; i++, y++)
    {
        newRoute[i] = *((int*)pTS->path + swapEnd - y);
        //printf("s%d ", newRoute[i]);
    }

    for (size_t i = swapEnd+1; i < pTS->pathSize; i++)
    {
        newRoute[i] = *((int*)pTS->path + i);
        //printf("%d ", newRoute[i]);
    }

    //printf("\n");
    return newRoute;
}

PathTS optimize2opt(PathTS pTS, Matriz m) {
    PathTS oldPath = calloc (1,sizeof(*oldPath));
    
    //Evitar que o pTS que seja desalocado criando uma copia 
    int* firstPath = calloc (pTS->pathSize, sizeof(int));
    int* firstValues = calloc (pTS->pathSize, sizeof(int));
    int firstSize = pTS->pathSize;
    
    for (size_t i = 0; i < pTS->pathSize; i++)
    {
        firstPath[i] = *(((int*)pTS->path)+i);
    }

     for (size_t i = 0; i < pTS->pathSize-1; i++)
    {
        firstValues[i] = *(((int*)pTS->value)+i);
    }
       
    oldPath->path = firstPath;
    oldPath->pathSize = firstSize;
    oldPath->value = firstValues;

    int newRouteValue = 0;
    int oldRouteValue = 0;
    int oldPathSize = pTS->pathSize;

   
   int improvement = 0;
   do {
        improvement = 0;
        oldRouteValue =  pathValue_int(oldPath->value, oldPath->pathSize);

        for (int i = 1; i <= pTS->pathSize-1; i++) {
            for (int j = i + 1; j < pTS->pathSize-1; j++) {

                //Nova rota
                int* newRoute = swap2opt(oldPath, i, j);
                //Peso dos Path
                int* newPesosRoute = calloc(m->size_x, sizeof(int));
                for (size_t i = 1; i <= m->size_x; i++) { 
                    newPesosRoute[i-1] = *(((int*)m->nodeVal) + (newRoute[i-1]* m->size_y) + newRoute[i] );
                }
                //Valor do novo Path
                newRouteValue = pathValue_int(newPesosRoute, oldPath->pathSize);

                if(newRouteValue < oldRouteValue){
                    //printf("\nEntrou aqui %d , old %d  ", newRouteValue , oldRouteValue);printf("\nnewRoute : ");for (size_t i = 0; i < 11; i++){printf("%d ", newRoute[i]);}printf("\nnewPesos : ");for (size_t i = 0; i < 10; i++){printf("%d ", newPesosRoute[i]);}printf("\n\n");
                
                    free(oldPath->path);
                    free(oldPath->value);
                    free(oldPath);
                    oldPath = PathTSinit_int(newRoute, newPesosRoute, oldPathSize);
                    improvement = 1;
                    break;
                }

                free(newPesosRoute);
                free(newRoute);
            }
            if(improvement == 1){
                break;
            }
        }
    } while(improvement == 1);

   return oldPath;
}


/**/
PathTS PathTSrandom_int(Matriz m) {

   //Preparando array auxiliar com tamanhos de [1, MatrizTamanho-1] (-1 pq inicia com 0)
    int tamanho = m->size_x - 1;
    int* entradasPossiveis = (int*) malloc (tamanho * sizeof(int));
    for (size_t i = 0; i < tamanho; i++) {entradasPossiveis[i] = i+1;}
    
    //Preparando array PathRandom com tamanho [MatrizTamanho + 1] Pois é uma pathTS
    int* entradasPath = calloc (m->size_x +1, sizeof(int));
    entradasPath[0] = 0;

    //Iniciar criação do path com random
    srand(time(0));

    for (size_t i = 0; i < tamanho; i++) {
        //Sempre decrementa o tamanho do array que estamos rodando
        int posicao = rand()%(tamanho-i);

        //printf("entradasPossivel[%d] = %d  ,  ",posicao, entradasPossiveis[posicao]);

        //Usado um auxiliar para evitar Dangling pointer
        int aux = entradasPossiveis[posicao];
        entradasPath[i+1] = aux;

        //Se a posição escolhida não é a ultima do array, pegamos a posição escolhida e trocamos com o ultimo valor
        //para evitar repetições (o rand posição ja diminui o tamanho a cada interação do for)
        if(posicao != (tamanho-i)-1) {
            entradasPossiveis[posicao] = entradasPossiveis[(tamanho-i)-1];
            entradasPossiveis[(tamanho-i)-1] = aux;
        }

        //printf("Entradas possiveis atuais ");
        //for (size_t i = 0; i < tamanho; i++) {printf("%d ", entradasPossiveis[i]);}
        //printf("\n");
    }

    entradasPath[m->size_x] = 0;

    //printf("Entradas escolhidas : "); 
    //for (size_t i = 0; i < tamanho+2; i++){printf("%d ", entradasPath[i]);} 
    //printf("\n");

    //Calculando custo do caminho
    int* valueCaminho = calloc(1, sizeof(int));
    for (size_t i = 1; i <= m->size_x; i++){ *valueCaminho += *(((int*)m->nodeVal) + (entradasPath[i-1]* m->size_y) + entradasPath[i] );}
    printf("Custo do caminho : %d\n", *valueCaminho);

    PathTS p = PathTSinit_int(entradasPath, valueCaminho, m->size_x+1); 
    
    entradasPath = 0;
    free(entradasPath);
    valueCaminho = 0;
    free(valueCaminho);
    free(entradasPossiveis);

    return p;
}

/**/
int positionValue_int(void* path, int size, int number){
    
    for (int i = 0; i < size+1; i++)
    {
        if( number == *((int*)path + i)){
            return i;
        }
    }
    return 0;
}

/**/
int pathValue(int* path, int size){
    int value = 0;

    for (int i = 0; i < size; i++)
    {
        value += path[i];
    }
    return value;
}

/**/
int pathValue_int(void* pathValues, int size) {
    int value = 0;

    for (int i = 0; i < size-1; i++)
    {
        value += *((int*)pathValues + i);
    }
    return value;
}

int pTSValue_int(void* pathValues, int init, int end) {
    int value = 0;

    for (int i = init; i < end; i++)
    {
        value += *((int*)pathValues + i);
    }
    return value;
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

    //Iniciando array com todas os pesos de zero 
    int* pesosEntradas = calloc (mSizeMinus1, sizeof(int));
    for (int i = 0; i < mSizeMinus1; i++)
    {
        pesosEntradas[i] = MATRIZelementoPesos_int(m, 0, i+1);
    }
    
    
    //Iniciar criação do path com random
    
    for (size_t i = 0; i < mSizeMinus1; i++)
    {
        
        int pVal = pathValue(pesosEntradas, mSizeMinus1-i);
        int vRand = rand()%pVal; //Valor randomizado dos pesos possiveis

        int y = 0;
        do
        {
            int breakAtual =  pathValue(pesosEntradas, y+1);
            if (vRand < breakAtual)
            {
                //printf("Entrou aqui y no array %d, valor no array = %d, vRand = %d , breakAtual = %d\n", y, entradasPossiveis[y], vRand, breakAtual);
                
                int aux = entradasPossiveis[y];
                entradasPath[i+1] = aux;

                if(y != (mSizeMinus1-i)) {
                    entradasPossiveis[y] = entradasPossiveis[(mSizeMinus1-i)-1];
                }

                for (int i = 0; i < mSizeMinus1-i; i++)
                {
                    pesosEntradas[i] = MATRIZelementoPesos_int(m, aux, entradasPossiveis[i]);
                }

                break;
            }
            y++;
        } while (y < mSizeMinus1-i);
    }

    free(pesosEntradas);
    free(entradasPossiveis);
    return entradasPath;
}

PathTS PathTSrandGuloso_int(Matriz m){
    int* pathResult = arrayRandGuloso_int(m);
     //Calculando custo do caminho

    int* valueCaminho = calloc(m->size_x, sizeof(int));
    for (size_t i = 1; i <= m->size_x; i++)
    { 
        valueCaminho[i-1] = *(((int*)m->nodeVal) + (pathResult[i-1]* m->size_y) + pathResult[i] );
    }
    //printf("Custo do caminho : %d\n", *valueCaminho);

    PathTS p = PathTSinit_int(pathResult, valueCaminho, m->size_x+1); 
    return p;
}

//PRINT's
void PathTSprint_int(PathTS p){
    if(p->path != NULL && p->value != NULL){
        printf("Path = ");
        for (size_t i = 0; i < p->pathSize; i++) {printf("%d ", *(((int*)p->path)+i)); }
        printf("\n");
        printf("Path Values = ");
        for (int i = 0; i < p->pathSize-1; i++) { printf("%d ", *((int*)p->value + i)); }
        printf("\n");
        printf("PathValue = %d\n", pathValue_int(p->value, p->pathSize));
        printf("PathSize = %d\n", p->pathSize);
    }else {
        printf("Path mal definido\n");
    }
}