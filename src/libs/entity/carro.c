#include <carro.h>

Carro carroInit(int numCarPassageiros) {
    if(numCarPassageiros < 0 ) {
        return NULL;
    }
    
    Carro car = calloc (1, sizeof(*car));
    car->numMaxPassageiros = numCarPassageiros;
    return car;
}

void carroPrint(Carro car){
     if(car != NULL){
        printf("Imprimindo carro\n");
        printf("Tamanho do Carro : %d \n", car->numMaxPassageiros);
    }else {
        printf("Carro mal definido\n");
    }
}