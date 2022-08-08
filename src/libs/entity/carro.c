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
     if(car != NULL) {
        printf("Imprimindo carro\n");
        printf("Car Size : %d\n", car->numMaxPassageiros);
    }else {
        printf("Car mal definido\n");
    }
}

void printCarInFile(const char fileName[], Car car){
    FILE *fp;
    int result;

    if ( (fp= fopen(fileName, "a+") ) != NULL) {
        
        if(car != NULL) {
            result = fprintf(fp,"Car Size : %d\n", car->numMaxPassageiros);  					          
        } else {
           result = fprintf(fp,"Car Not Well defined");  					    	 
        }

        if (result == EOF) {
            printf("Erro na Gravacao aqui\n");	
        }
        
        fclose(fp);
    }else {
        printf("Erro na Gravacao aqui\n");				    	 
    }
}

void freeCar(Car c) {
    free(c);
}