#include <passageiros.h>

//INIT's
/* Cria um passageiro com seus respectivos valores*/
Passageiros pListInit(int* entry, int* out, float* value, float* payValue, int size){
    if(entry == NULL || out == NULL || value == NULL || payValue == NULL || size < 0){
        return NULL;
    }

    Passageiros p = calloc(1, sizeof(*p));
    p->origem = entry;
    p->destino = out;
    p->valorMaximo = value;
    p->valorPago = payValue;
    p->listSize = size;

    return p;
}


/*Retorna um array de passageiros que satisfazem o path*/
Passageiros pListOnPath(Passageiros passengerList, PathTS pathTS, Carro car) {
    
    int* passNoCarro = calloc(car->numMaxPassageiros, sizeof(int)); //Array com tamanho maximo de passageiros no carro que guarda a posicao no array de passageiros daquele passageiro que acabou de entrar
    for (int i = 0; i < car->numMaxPassageiros; i++){ passNoCarro[i] = -1;}//Inicializa com valor impossivel
    
    int* passAtendidosList = calloc(passengerList->listSize, sizeof(int)); //Array com tamanho maximo de passageiros guarda a posicao no array de passageiros já entraram no carro
    for (int i = 0; i < car->numMaxPassageiros; i++){ passAtendidosList[i] = -1;}//Inicializa com valor impossivel

    float* passValApagarList = calloc(passengerList->listSize, sizeof(float)); //Array com tamanho maximo de passageiros guarda o valor que o passageiros irá pagar ao sair do carro

    int numPassAtendidos = 0; //Tamanho utilizado para saber quantos passageiros foram atendidos
    int nAtualPassNoCarro = 0; //Cont o valor dos passageiros atualmente no carro
    
    
    //Inicio do algoritmo
    for (int posicaoAtual = 0; posicaoAtual < pathTS->pathSize; posicaoAtual++)
    {
        //Atualizando valores pagos
        if (posicaoAtual > 0)
        {
            for (int i = 0; i < car->numMaxPassageiros; i++)
            {
                //Verifica se existe alguem no carro
                if (passNoCarro[i] != -1)//Evitar acesso de memoria incorreto
                {
                    float valorCaminho = *(((int*)pathTS->value)+posicaoAtual-1);//-1 pq o primeiro valor do pathTS->value é a aresta [0->1] 
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
                    if (passengerList->destino[passNoCarro[j]] == *(((int*)pathTS->path)+posicaoAtual)) { 
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
            for (int i = 1; i < posicaoAtual; i++) //Começa em 1 para que quem entrar depois do zero, possa voltar ao zero
            {
                //Testa se o destino já foi percorrido do passageiro que entraria agora 
                int passDestino = passengerList->destino[*(((int*)pathTS->path)+posicaoAtual)];
                if(passDestino == *(((int*)pathTS->path)+i)){
                    fPosicaoJaPercorrida = 1;
                }
            }

            //Se não foi percorrido
            if( fPosicaoJaPercorrida == 0)
            {
                int saida = positionValue_int( pathTS->path, pathTS->pathSize,  passengerList->destino[*(((int*)pathTS->path)+posicaoAtual)]);
                
                //Só rodar ele e o motorista 
                if( (pTSValue_int(pathTS->value, posicaoAtual, saida)/2) < passengerList->valorMaximo[posicaoAtual] ){
                    for (int j = 0; j < car->numMaxPassageiros; j++)
                    {
                        if (passNoCarro[j] == -1)
                        {   

                        passNoCarro[j] = *(((int*)pathTS->path)+posicaoAtual);
                        nAtualPassNoCarro++;
                        
                        passAtendidosList[numPassAtendidos] = *(((int*)pathTS->path)+posicaoAtual);
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

    return pListInit(pAtendidosListOrigem, pAtendidosListDestino,pAtendidosListValorMaximo, pAtendidosListValorPago, numPassAtendidos);
}

//PRINTS's
/* Imprime as informações do passageiro*/
void passageiroPrint(Passageiros passengersList) {
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
 