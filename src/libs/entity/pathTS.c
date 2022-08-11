#include <pathTS.h>

//INIT


/**/
PathTS iPathTS_int(int* pathCaminho, int* valuePath, int pathTamanho) {
    PathTS p = calloc (1,sizeof(*p));
    p->path = pathCaminho;
    p->totalValue = valuePath;
    p->pathSize = pathTamanho;
    p->numPassengersOnPath = 0;
    return p;
}

//FUNCTIONS

int calculePathValue(int* pathCaminho, int pathTamanho, Matriz m){
    int val = 0;
    for (size_t i = 1; i <= m->size_x; i++) { 
        val += getMatrizElementValue_int(m, pathCaminho[i-1], pathCaminho[i]);
    }

    return val;
}


/**/
int sumArrayElements(int* path, int size){
    int value = 0;

    for (int i = 0; i < size; i++)
    {
        value += path[i];
    }
    return value;
}

//PRINT's
void printPathTS_int(PathTS p, Matriz m) {
     if(p->path != NULL) {
            //Imprime caminho
            fprintf(stdout, "Path = ");
            for (size_t i = 0; i < p->pathSize; i++) {
                fprintf(stdout, "%d ", *(((int*)p->path)+i)); 
            }
            fprintf(stdout, "\n");

            //Imprime valores do caminho
            fprintf(stdout, "Path Values = ");
            for (int i = 0; i < p->pathSize-1; i++) {  
                int positBegin = *(((int*)p->path)+i);
                int positEnd = *(((int*)p->path)+i+1);
                fprintf(stdout, "%d ", getMatrizElementValue_int(m,positBegin, positEnd)); 
            }
            fprintf(stdout,"\n");

            //Imprime Valor total do caminho
            fprintf(stdout, "PathValue = %d\n", *((int*)p->totalValue));
            fprintf(stdout, "Numero de passageiros = %d\n", p->numPassengersOnPath);
        }
}

/**/
void printPathTSInFile_int(const char fileName[], PathTS p, Matriz m, int contador) {
    FILE *fp;

    if ( (fp= fopen(fileName, "a+") ) != NULL) {
        
        if(p->path != NULL) {
            //Imprime caminho
            if (contador != -1)
            {
               fprintf(fp, "Path %d\n", contador);
            }
            
            fprintf(fp, "Path = ");
            for (size_t i = 0; i < p->pathSize; i++) {
                fprintf(fp, "%d ", *(((int*)p->path)+i)); 
            }
            fprintf(fp, "\n");

            //Imprime valores do caminho
            fprintf(fp, "Path Values = ");
            for (int i = 0; i < p->pathSize-1; i++) {  
                int positBegin = *(((int*)p->path)+i);
                int positEnd = *(((int*)p->path)+i+1);
                fprintf(fp, "%d ", getMatrizElementValue_int(m,positBegin, positEnd)); 
            }
            fprintf(fp,"\n");

            //Imprime Valor total do caminho
            fprintf(fp, "PathValue = %d\n", *((int*)p->totalValue));
            fprintf(fp, "Numero de passageiros = %d\n\n", p->numPassengersOnPath);
        }
        fclose(fp);
    }else {
        printf("Erro na Gravacao printPathTSInFile_int\n");				    	 
    }
}


void freePath(PathTS pTS) {
    free(pTS->path);
    free(pTS->totalValue);
    free(pTS);
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

int pTSValue_int(void* pathValues, int init, int end, Matriz m) {
    
    int value = 0;

    for (int i = init; i < end; i++)
    {
        int positBegin = *((int*)pathValues + i);
        int positEnd = *((int*)pathValues + i+1);
        value += getMatrizElementValue_int(m, positBegin, positEnd);
    }
    return value;
}