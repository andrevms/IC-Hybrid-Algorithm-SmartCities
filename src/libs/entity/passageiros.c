#include <passageiros.h>

//INIT's
/* Cria um passageiro com seus respectivos valores*/
ListPassageiros initListPassageiros(int* entry, int* out, float* value, float* payValue, int size){
    if(entry == NULL || out == NULL || value == NULL || payValue == NULL || size < 0){
        return NULL;
    }

    ListPassageiros p = calloc(1, sizeof(*p));
    p->origem = entry;
    p->destino = out;
    p->valorMaximo = value;
    p->valorPago = payValue;
    p->listSize = size;

    return p;
}


/*Retorna um array de passageiros que satisfazem o path*/
ListPassageiros boardPassengersOnPath(ListPassageiros passengerList, PathTS pathTS, Car car, Matriz m) {

    //Condição de saidas
    if (passengerList == NULL || pathTS == NULL || car == NULL) { return NULL; }
    
    //Array com tamanho maximo de passageiros no carro que guarda a posicao no array de passageiros daquele passageiro que acabou de entrar
    int* passNoCarro = calloc(car->numMaxPassageiros, sizeof(int));
    //Inicializa com valor impossivel 
    for (int i = 0; i < car->numMaxPassageiros; i++){ passNoCarro[i] = -1;}
    
    //Array com tamanho maximo de passageiros guarda a posicao no array de passageiros já entraram no carro
    int* passAtendidosList = calloc(passengerList->listSize, sizeof(int));
    //Inicializa com valor impossivel 
    for (int i = 0; i < car->numMaxPassageiros; i++){ passAtendidosList[i] = -1;}

    //Array com tamanho maximo de passageiros guarda o valor que o passageiros irá pagar ao sair do carro
    float* passValApagarList = calloc(passengerList->listSize, sizeof(float)); 

    //Tamanho utilizado para saber quantos passageiros foram atendidos
    int numPassAtendidos = 0; 
    //Cont o valor dos passageiros atualmente no carro
    int nAtualPassNoCarro = 0; 
    
    
    //Inicio do algoritmo
    for (int iAtual = 0; iAtual < pathTS->pathSize; iAtual++)
    {
        //Atualizando valores pagos pelos Passageiros se existir alguem no carro
        if (iAtual > 0 && nAtualPassNoCarro > 0)
        {
            //Verifica se existe alguem no carro
            for (int i = 0; i < car->numMaxPassageiros; i++)
            {
                if (passNoCarro[i] != -1)//Evitar acesso de memoria incorreto
                {
                    int positBegin = *(((int*)pathTS->path)+ iAtual-1);
                    int positEnd = *(((int*)pathTS->path)+ iAtual);
                    float valorCaminho = getMatrizElementValue_int(m, positBegin, positEnd);
                    passValApagarList[passNoCarro[i]] += valorCaminho/(nAtualPassNoCarro+1);//+1 por causa do motorista
                }
            }
        }
        
        //Testa se tem alguem para sair do carro
        if(nAtualPassNoCarro > 0) { // tem alguem no carro?
            for (int j = 0; j < car->numMaxPassageiros; j++)
            {   
                //Verifica se existe algum destino igual a posição atual do carro
                if (passNoCarro[j] != -1)//Evitar acesso de memoria incorreto
                {
                    if (passengerList->destino[passNoCarro[j]] == *(((int*)pathTS->path)+iAtual)) { 
                        //Finaliza corrida do Passageiro
                        passNoCarro[j] = -1; 
                        nAtualPassNoCarro--;
                    } 
                }
            }
        }

        //Testa se tem alguem para entrar no carro
        if(nAtualPassNoCarro < car->numMaxPassageiros) { // tem espaço no carro?

            int fPosicaoJaPercorrida = 0;
            for (int i = 1; i < iAtual; i++) //Começa em 1 para que quem entrar depois do zero, possa voltar ao zero
            {
                //Testa se o destino já foi percorrido do passageiro que entraria agora 
                int passDestino = passengerList->destino[*(((int*)pathTS->path)+iAtual)];
                if(passDestino == *(((int*)pathTS->path)+i)){
                    fPosicaoJaPercorrida = 1;
                }
            }

            //Se não foi percorrido
            if( fPosicaoJaPercorrida == 0)
            {
                int saida = positionValue_int( pathTS->path, pathTS->pathSize,  passengerList->destino[*(((int*)pathTS->path)+iAtual)]);
                
                //Só rodar ele e o motorista 
                if( (pTSValue_int(pathTS->path, iAtual, saida, m)/2) < passengerList->valorMaximo[iAtual] ){
                    for (int j = 0; j < car->numMaxPassageiros; j++)
                    {
                        if (passNoCarro[j] == -1)
                        {   

                        passNoCarro[j] = *(((int*)pathTS->path)+iAtual);
                        nAtualPassNoCarro++;
                        
                        passAtendidosList[numPassAtendidos] = *(((int*)pathTS->path)+iAtual);
                        numPassAtendidos++;
                        break;
                        }
                    }
                }
               
            }
        }
    }

    int* pAtendidosListOrigem = calloc(numPassAtendidos, sizeof(int));
    int* pAtendidosListDestino = calloc(numPassAtendidos, sizeof(int));
    float* pAtendidosListValorMaximo = calloc(numPassAtendidos, sizeof(float));
    float* pAtendidosListValorPago = calloc(numPassAtendidos, sizeof(float));

    for (size_t i = 0; i < numPassAtendidos; i++) { pAtendidosListValorPago[i] = passValApagarList[passAtendidosList[i]]; }
    
    for (size_t i = 0; i < numPassAtendidos; i++)
    {
        pAtendidosListOrigem[i] = passengerList->origem[passAtendidosList[i]];
        pAtendidosListDestino[i] = passengerList->destino[passAtendidosList[i]];
        pAtendidosListValorMaximo[i] = passengerList->valorMaximo[passAtendidosList[i]];
    }
    
    free(passAtendidosList);
    free(passNoCarro);
    free(passValApagarList);

    return initListPassageiros(pAtendidosListOrigem, pAtendidosListDestino,pAtendidosListValorMaximo, pAtendidosListValorPago, numPassAtendidos);
}

/*Retorna um array de passageiros que satisfazem o path*/
ListPassageiros boardPassengers(ListPassageiros passengerList, int* pathTS, Car car, Matriz m) {

    int pathSize = m->size_x+1;

    //Condição de saidas
    if (passengerList == NULL || pathTS == NULL || car == NULL) { return NULL; }
    
    //Array com tamanho maximo de passageiros no carro que guarda a posicao no array de passageiros daquele passageiro que acabou de entrar
    int* passNoCarro = calloc(car->numMaxPassageiros, sizeof(int));
    //Inicializa com valor impossivel 
    for (int i = 0; i < car->numMaxPassageiros; i++){ passNoCarro[i] = -1;}
    
    //Array com tamanho maximo de passageiros guarda a posicao no array de passageiros já entraram no carro
    int* passAtendidosList = calloc(passengerList->listSize, sizeof(int));
    //Inicializa com valor impossivel 
    for (int i = 0; i < car->numMaxPassageiros; i++){ passAtendidosList[i] = -1;}

    //Array com tamanho maximo de passageiros guarda o valor que o passageiros irá pagar ao sair do carro
    float* passValApagarList = calloc(passengerList->listSize, sizeof(float)); 

    //Tamanho utilizado para saber quantos passageiros foram atendidos
    int numPassAtendidos = 0; 
    //Cont o valor dos passageiros atualmente no carro
    int nAtualPassNoCarro = 0; 
    
    
    //Inicio do algoritmo
    for (int iAtual = 0; iAtual < pathSize; iAtual++)
    {
        //Atualizando valores pagos pelos Passageiros se existir alguem no carro
        if (iAtual > 0 && nAtualPassNoCarro > 0)
        {
            //Verifica se existe alguem no carro
            for (int i = 0; i < car->numMaxPassageiros; i++)
            {
                if (passNoCarro[i] != -1)//Evitar acesso de memoria incorreto
                {
                    int positBegin = pathTS[iAtual-1];
                    int positEnd = pathTS[iAtual];
                    float valorCaminho = getMatrizElementValue_int(m, positBegin, positEnd);
                    passValApagarList[passNoCarro[i]] += valorCaminho/(nAtualPassNoCarro+1);//+1 por causa do motorista
                }
            }
        }
        
        //Testa se tem alguem para sair do carro
        if(nAtualPassNoCarro > 0) { // tem alguem no carro?
            for (int j = 0; j < car->numMaxPassageiros; j++)
            {   
                //Verifica se existe algum destino igual a posição atual do carro
                if (passNoCarro[j] != -1)//Evitar acesso de memoria incorreto
                {
                    if (passengerList->destino[passNoCarro[j]] == pathTS[iAtual]) { 
                        //Finaliza corrida do Passageiro
                        passNoCarro[j] = -1; 
                        nAtualPassNoCarro--;
                    } 
                }
            }
        }

        //Testa se tem alguem para entrar no carro
        if(nAtualPassNoCarro < car->numMaxPassageiros) { // tem espaço no carro?

            int fPosicaoJaPercorrida = 0;
            for (int i = 1; i < iAtual; i++) //Começa em 1 para que quem entrar depois do zero, possa voltar ao zero
            {
                //Testa se o destino já foi percorrido do passageiro que entraria agora 
                int passDestino = passengerList->destino[pathTS[iAtual]];
                if(passDestino == pathTS[i]){
                    fPosicaoJaPercorrida = 1;
                }
            }

            //Se não foi percorrido
            if( fPosicaoJaPercorrida == 0)
            {
                int saida = positionValue_int( pathTS, pathSize,  passengerList->destino[pathTS[iAtual]]);
                
                //Só rodar ele e o motorista 
                if( (pTSValue_int(pathTS, iAtual, saida, m)/2) < passengerList->valorMaximo[iAtual] ){
                    for (int j = 0; j < car->numMaxPassageiros; j++)
                    {
                        if (passNoCarro[j] == -1)
                        {   

                        passNoCarro[j] = pathTS[iAtual];
                        nAtualPassNoCarro++;
                        
                        passAtendidosList[numPassAtendidos] = pathTS[iAtual];
                        numPassAtendidos++;
                        break;
                        }
                    }
                }
               
            }
        }
    }

    int* pAtendidosListOrigem = calloc(numPassAtendidos, sizeof(int));
    int* pAtendidosListDestino = calloc(numPassAtendidos, sizeof(int));
    float* pAtendidosListValorMaximo = calloc(numPassAtendidos, sizeof(float));
    float* pAtendidosListValorPago = calloc(numPassAtendidos, sizeof(float));

    for (size_t i = 0; i < numPassAtendidos; i++) { pAtendidosListValorPago[i] = passValApagarList[passAtendidosList[i]]; }
    
    for (size_t i = 0; i < numPassAtendidos; i++)
    {
        pAtendidosListOrigem[i] = passengerList->origem[passAtendidosList[i]];
        pAtendidosListDestino[i] = passengerList->destino[passAtendidosList[i]];
        pAtendidosListValorMaximo[i] = passengerList->valorMaximo[passAtendidosList[i]];
    }
    
    free(passAtendidosList);
    free(passNoCarro);
    free(passValApagarList);

    return initListPassageiros(pAtendidosListOrigem, pAtendidosListDestino,pAtendidosListValorMaximo, pAtendidosListValorPago, numPassAtendidos);
}


//PRINTS's
/* Imprime as informações do passageiro*/
void printListPassengers(ListPassageiros passengersList) {
    if(passengersList != NULL) {
        printf("Imprimindo passageiros\n");
        if (passengersList->listSize == 0 ) {
            printf("Nao foi encontrado nenhum passageiro\n");
        } else {
            for (int i = 0; i < passengersList->listSize; i++) { 
                printf("Passageiro[%d] O->%d D->%d MaxVal->%f payVal = %f\n",
                        i, 
                        passengersList->origem[i], 
                        passengersList->destino[i], 
                        passengersList->valorMaximo[i], 
                        passengersList->valorPago[i]
                        );
            }
            printf("\n");
        }
    } else {
        printf("Passageiro mal definido\n");
    }
}

/**/
void printListPassengersInFile(const char fileName[], ListPassageiros passengersList){
    FILE *fp;
    if ( (fp= fopen(fileName, "a+") ) != NULL) {
        
       for (int i = 0; i < passengersList->listSize; i++) { 
            fprintf(fp, "Passageiro[%d] O->%d D->%d MaxVal->%f payVal = %f\n",
                        i, 
                        passengersList->origem[i], 
                        passengersList->destino[i], 
                        passengersList->valorMaximo[i], 
                        passengersList->valorPago[i]
                        );
        }
            fprintf(fp,"\n");
        fclose(fp);
    }else {
        printf("Erro na Gravacao aqui\n");				    	 
    }
}


void freeListPassengers(ListPassageiros p) {
    free(p->origem);
    free(p->destino);
    free(p->valorMaximo);
    free(p->valorPago);
    free(p);
}