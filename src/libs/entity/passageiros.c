#include <passageiros.h>

//INIT's
/* Cria um passageiro com seus respectivos valores*/
Passageiros pListInit(int* entry, int* out, float* value, int size){
    Passageiros p = calloc(1, sizeof(*p));
    p->origem = entry;
    p->destino = out;
    p->valorMaximo = value;
    p->listSize = size;
    return p;
}

//PRINTS's
/* Imprime as informações do passageiro*/
void passageiroPrint(Passageiros p) {

  
    if(p != NULL){
        printf("Imprimindo passageiros\n");
        for (int i = 0; i < p->listSize; i++){ printf("Passageiro[%d] O->%d D->%d MaxVal->%f\n",i, p->origem[i], p->destino[i], p->valorMaximo[i]);}
        printf("\n");
    }else {
        printf("Passageiro mal definido\n");
    }
}
 