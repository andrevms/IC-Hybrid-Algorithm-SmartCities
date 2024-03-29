#include <matrizAdjacente.h>


// INIT's
/**/
Matriz initMatrizWithArray_int(int row, int col, int* vetor) {
    Matriz m = calloc ( 1, sizeof(*m));
    m->size_x = row;
    m->size_y = col;
    m->nodeVal = vetor;
    
    return m;
}
/**/
Matriz initMatrizWithVal_int(int row, int col, int val) {
    Matriz m = calloc ( 1, sizeof(*m));
    m->size_x = row;
    m->size_y = col;
    m->nodeVal = calloc ( (row * col), sizeof(int));

    //init nodeVal com val
    int last_val = m->size_x * m->size_y;
    if(m->nodeVal != NULL) {
        for (int i = 0; i < last_val; i++) {
            *((int*)m->nodeVal+i) = val;
        }
    } else {
        printf("Erro na alocação do nodeVal -> initMatrizWithVal_int\n");
    }

    return m;
}

/**/
Matriz initMatriz() {
    Matriz m = calloc ( 1, sizeof(*m));
    return m;
}

//Functions

/**/
int* getMatrizRowValues_int(Matriz m, int row){
    int* pesosEntradas = calloc (m->size_x, sizeof(int));

    for (int i = 0; i < m->size_x; i++)
    {
        pesosEntradas[i] =  *(((int*)m->nodeVal)+ ((row *m->size_y)+i));
    }

    return pesosEntradas;
}

/**/
int getMatrizElementValue_int(Matriz m, int row, int col){
    if(row > m->size_x || col > m->size_y){
        printf("Erro MATRIZelemntoPesos_int, acesso indevido de variavel");
        exit(-1);
    }
    return *(((int*)m->nodeVal)+ ((row *m->size_y)+ col));
}

//Print's
/**/
void printMatriz_int(Matriz m) {

    printf("\nImprimindo matriz\n");
    printf("Numero de linhas = %d\n", m->size_x);
    printf("Numero de colunas = %d\n", m->size_y);
    
    int last_val = m->size_x * m->size_y;

    if(m->nodeVal != NULL) {
        for (int i = 0; i < last_val; i++) {
            if (i%m->size_y == 0)
            {
                printf("\n%d ", *(((int*)m->nodeVal)+i)); 
            } else{
                printf("%d ", *(((int*)m->nodeVal)+i));
            }
        }
    } else {
        printf("Matriz adjacente ainda não definida\n");
    }
    printf("\n\n");
}

/**/
void printMatrizInFile_int(const char fileName[], Matriz m){
    FILE *fp;
    int result;

    if ( (fp= fopen(fileName, "a+") ) != NULL) {
        
        if(m != NULL) {
            result = fprintf(fp,"Numero de linhas = %d\nNumero de colunas = %d\n", m->size_x, m->size_y);
            if (result == EOF) {
                printf("Erro na Gravacao printMatirzInFile_int m->size_x, m->size_y\n");	
                exit(-1);
            }

            int last_val = m->size_x * m->size_y;

            if(m->nodeVal != NULL) {
                for (int i = 0; i < last_val; i++) {
                    if (i%m->size_y == 0)
                    {
                        result = fprintf(fp,"\n%d ", *(((int*)m->nodeVal)+i));
                        if (result == EOF) { //Testes se salvou direito
                            printf("Erro na Gravacao printMatirzInFile_int m->size_x, m->size_y\n");	
                            exit(-1);
                        } 
                    } else{
                        result = fprintf(fp,"%d ", *(((int*)m->nodeVal)+i));
                        if (result == EOF) {
                            printf("Erro na Gravacao printMatirzInFile_int m->size_x, m->size_y\n");	
                            exit(-1);
                        }
                    }
                }
                fprintf(fp,"\n\n");
            }
        } else {
           result = fprintf(fp,"Matriz Not Well defined");  					    	 
        }
        fclose(fp);
    }else {
        printf("Erro na Gravacao aqui\n");				    	 
    }
}

//FREE

void freeMatriz(Matriz m) {
    free(m->nodeVal);
    free(m);
}