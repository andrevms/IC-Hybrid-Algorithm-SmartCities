#include <passageiros.h>

//INIT's
/* Cria um passageiro com seus respectivos valores*/
Passageiros pListInit(int* entry, int* out, float* value, float* payValue, int size){
    Passageiros p = calloc(1, sizeof(*p));
    p->origem = entry;
    p->destino = out;
    p->valorMaximo = value;
    p->valorPago = payValue;
    p->listSize = size;
    return p;
}


/*Retorna um array de passageiros que satisfazem o path*/
Passageiros pListOnPath(Passageiros p, PathTS pTS, Carro c) {
    
    //Array com maximo de passageiros possiveis
    int* origemPassAtendidoList = calloc(p->listSize, sizeof(int)); //Guarda apenas a origem dos passageiros
    int passageirosAtendidos = 0;

    //Destinos dos passageiros dentro do carro (Maximo de Passageiros = numMaxPassageiros)
    int* destinos = calloc(c->numMaxPassageiros, sizeof(int));
    for (size_t i = 0; i < c->numMaxPassageiros; i++){ destinos[i] = -1;}
    
    //Cont o valor dos passageiros atualmente no carro
    int nAtualPassNoCarro = 0;
    
    for (int posicaoAtual = 0; posicaoAtual < pTS->pathSize; posicaoAtual++)
    {
        //Testa se tem alguem para sair do carro
        if(nAtualPassNoCarro > 0) { // tem alguem no carro?
            for (size_t j = 0; j < c->numMaxPassageiros; j++)
            {
                if (destinos[j] == posicaoAtual) { 
                    destinos[j] = -1; 
                    nAtualPassNoCarro--;
                } 
            }
        }
        
        //Testa se tem alguem para entrar no carro
        if(nAtualPassNoCarro < c->numMaxPassageiros) { // tem espaço no carro?
            for (size_t j = 0; j < 3; j++)
            {
                if (destinos[j] == -1)
                {
                   destinos[j] = p->destino[*(((int*)pTS->path)+posicaoAtual)];
                   nAtualPassNoCarro++;
                   origemPassAtendidoList[passageirosAtendidos] = p->origem[*(((int*)pTS->path)+posicaoAtual)];
                   passageirosAtendidos++;
                   break;
                }
            }
        }
    }



    int* pAtendidosListOrigem = calloc(passageirosAtendidos, sizeof(int));
    int* pAtendidosListDestino = calloc(passageirosAtendidos, sizeof(int));
    float* pAtendidosListValorMaximo = calloc(passageirosAtendidos, sizeof(float));
    float* pAtendidosListValorPago = calloc(passageirosAtendidos, sizeof(float));

    for (size_t i = 0; i < passageirosAtendidos; i++)
    {
        pAtendidosListOrigem[i] = p->origem[origemPassAtendidoList[i]];
        pAtendidosListDestino[i] = p->destino[origemPassAtendidoList[i]];
        pAtendidosListValorMaximo[i] = p->valorMaximo[origemPassAtendidoList[i]];
        pAtendidosListValorPago[i] = p->valorPago[origemPassAtendidoList[i]];
    }
    
    free(origemPassAtendidoList);
    free(destinos);

    return pListInit(pAtendidosListOrigem, pAtendidosListDestino,pAtendidosListValorMaximo, pAtendidosListValorPago, passageirosAtendidos);

}

//PRINTS's
/* Imprime as informações do passageiro*/
void passageiroPrint(Passageiros p) {
  
    if(p != NULL){
        printf("Imprimindo passageiros\n");
        for (int i = 0; i < p->listSize; i++){ printf("Passageiro[%d] O->%d D->%d MaxVal->%f payVal = %f\n",i, p->origem[i], p->destino[i], p->valorMaximo[i], p->valorPago[i]);}
        printf("\n");
    }else {
        printf("Passageiro mal definido\n");
    }
}
 