//#include "telag.h"
#include "arvore.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Arv cria_arv(char *palavra){
    Arv arv = malloc(sizeof(struct arv));
    arv->palavra = palavra;
    arv->alt = 0;
    arv->largura = strlen(palavra);
    arv->dir = NULL;
    arv->esq = NULL;
    arv->x = 0;
    arv->y = 0;
    return arv;
}

void printa_arv(Arv base){
    if(base == NULL){
        printf("\n");
        return;
    }
    if(base->dir == NULL){ 
        printf("%s\n", base->palavra);
        return;
    }
    printf("    ");
    printa_arv(base->dir);
    printf("%s\n", base->palavra);
    printa_arv(base->esq);
}

Arv insere_arv(Arv base, Arv novo){
    if(base == NULL) return novo;
    if(strcmp(base->palavra, novo->palavra)>0){
        base = insere_arv(base->esq, novo);
    }
    else if(strcmp(base->palavra, novo->palavra)<0){
        base = insere_arv(base->dir, novo);
    }
    return base;
}

Arv remove_arv(Arv base, char *palavra){
    if(base == NULL) return base;
    if(strcmp(base->palavra, palavra)>0){
        remove_arv(base->esq, palavra);
    }
    else if(strcmp(base->palavra, palavra)<0){
        remove_arv(base->dir, palavra);
    }
    return base;
}
