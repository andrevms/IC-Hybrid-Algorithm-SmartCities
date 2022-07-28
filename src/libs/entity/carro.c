#include <carro.h>

Carro carroInit(int numCarPassageiros) {
    Carro c = calloc (1, sizeof(*c));
    c->numMaxPassageiros = numCarPassageiros;
    return c;
}

void carroPrint(Carro c){
     if(c != NULL){
        printf("Imprimindo carro\n");
        printf("Tamanho do Carro : %d \n", c->numMaxPassageiros);
    }else {
        printf("Carro mal definido\n");
    }
}