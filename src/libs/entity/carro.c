#include <carro.h>

Car initCarWithVal(int numCarPassageiros) {
    if(numCarPassageiros < 0 ) {
        return NULL;
    }
    
    Car car = calloc (1, sizeof(*car));
    car->numMaxPassageiros = numCarPassageiros;
    return car;
}

void printCar(Car car){
     if(car != NULL){
        printf("Imprimindo carro\n");
        printf("Tamanho do Car : %d \n", car->numMaxPassageiros);
    }else {
        printf("Car mal definido\n");
    }
}