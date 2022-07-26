#include <genericPath.h>
#include <matrizAdjacente.h>

//INIT
PathTS PathTSinit_int(int* pathCaminho, int* valuePath, int pathTamanho) {
    PathTS p = calloc (1,sizeof(*p));
    p->path = pathCaminho;
    p->value = valuePath;
    p->pathSize = pathTamanho;

    return p;
}



//FUNCTIONS

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

//TODO 
int* arrayRandGuloso_int(Matriz m){

    int mSizePlus1 = m->size_x +1;
    int mSizeMinus1 = m->size_x -1;
    
    //Preparando array auxiliar com tamanhos de [1, MatrizTamanho-1] (-1 pq inicia com 0)
    int* entradasPossiveis = calloc (mSizeMinus1, sizeof(int));
    for (size_t i = 0; i < mSizeMinus1; i++) {entradasPossiveis[i] = i+1;}

    //Preparando array PathRandom com tamanho [MatrizTamanho + 1] Pois é uma pathTS
    int* entradasPath = calloc (mSizePlus1, sizeof(int));
    entradasPath[0] = 0;

    //Iniciar criação do path com random
    srand(time(0));

    //for (size_t i = 0; i < mSizeMinus1; i++)
    //{
    //    
    //}
    
}

//TODO
PathTS PathTSrandGuloso_int(Matriz m){
    //int* pathResult = arrayRandGuloso_int(m);

    //Calculando custo do caminho
    //int valueCaminho = 0;
   // for (size_t i = 1; i <= m->size_x; i++){ valueCaminho += *(((int*)m->nodeVal) + (pathResult[i-1]* m->size_y) + pathResult[i] );}
    //printf("Custo do caminho : %d\n", valueCaminho);

    //PathTS p = PathTSinit_int(pathResult, &valueCaminho, m->size_x+1); 
   // return p;
}

//PRINT's
void PathTSprint_int(PathTS p){
    if(p->path != NULL && p->value != NULL){
        printf("PathSize = %d\n", p->pathSize);
        printf("PathValue = %d\n", *(int*)p->value);
        printf("Path = ");
        for (size_t i = 0; i < p->pathSize; i++) {printf("%d ", *(((int*)p->path)+i)); }
        printf("\n");
    }else {
        printf("Path mal definido\n");
    }
}