#include <carro.h>

Carro carroInit(int nPassageiros) {
    Carro c = calloc (1, sizeof(*c));
    c->num_passageiros = nPassageiros;
    c->passageirosNoCarro = 0;
    c->listPassageiro = calloc(nPassageiros, sizeof(int));
    for (size_t i = 0; i < nPassageiros; i++)
    {
        c->listPassageiro[i] = -1;
    }
    
    return c;
}

void carroPrint(Carro c){
     if(c != NULL){
        printf("Imprimindo carro\n");
        printf("Tamanho do Carro : %d \n", c->num_passageiros);
        printf("Passageiros no carro : %d \n", c->passageirosNoCarro);
        for (int i = 0; i < c->num_passageiros; i++){ 
            if(c->listPassageiro[i] != -1){
                printf("Passageiro[%d] entrou em [%d]",i, c->listPassageiro[i]);
            }
        }
        printf("\n");
    }else {
        printf("Passageiro mal definido\n");
    }
}