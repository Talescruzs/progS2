#include "listas.h"
#include <stdio.h>
#include <stdlib.h>

/* função de criação: retorna uma lista vazia */
Lista* lst_cria (void){
    return NULL;
}
Lista* lst_insere (Lista* l, int i){
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = l;
    return novo;
}
void lst_imprime(Lista *l){
    Lista *p;
    for(p = l; p != NULL; p=p->prox){
        printf("info = %d\n", p->info);
    }
}
int lst_vazia(Lista *l){
    return(l==NULL);
}
Lista* busca (Lista* l, int v){ 
    Lista* p;
    for (p=l; p!=NULL; p = p->prox) {
        if (p->info == v)
        return p;
    }
    return NULL; /* não achou o elemento */
}