#include <container.h>

Container containerInit( Matriz matriz, Passageiros pList, Carro carro){
    Container ct = calloc ( 1, sizeof(*ct));
    ct->m = matriz;
    ct->p = pList;
    ct->c = carro;
    return ct;
}