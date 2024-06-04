#include "telag.h"
#include "arvore.h"
#include <stdio.h>
#include <assert.h>

typedef struct arv{
    char * palavra;
    int x;
    int y;
    int alt;
    struct arv *dir;
    struct arv *esq;
} *Arv;

Arv cria_arv(void){
    
}
