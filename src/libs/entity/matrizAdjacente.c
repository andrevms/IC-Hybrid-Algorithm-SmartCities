#include <matrizAdjacente.h>


// INIT's
Matriz MATRIZinit_int(int row, int col, int* vetor) {
    Matriz m = calloc ( 1, sizeof(*m));
    m->size_x = row;
    m->size_y = col;
    m->nodeVal = vetor;
    
    return m;
}

Matriz MATRIZinit_intVal(int row, int col, int val) {
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
        printf("Erro na alocação do nodeVal -> MATRIZinit_intVal\n");
    }

    return m;
}


//Functions

int* MATRIZlinhaPesos_int(Matriz m, int row){
    int* pesosEntradas = calloc (m->size_x, sizeof(int));

    for (int i = 0; i < m->size_x; i++)
    {
        pesosEntradas[i] =  *(((int*)m->nodeVal)+ ((row *m->size_y)+i));
    }

    return pesosEntradas;
}

int MATRIZelementoPesos_int(Matriz m, int row, int col){
    if(row > m->size_x || col > m->size_y){
        printf("Erro MATRIZelemntoPesos_int, acesso indevido de variavel");
        exit(-1);
    }
    return *(((int*)m->nodeVal)+ ((row *m->size_y)+ col));
}

//Print's
void MATRIZprint_int(Matriz m) {

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