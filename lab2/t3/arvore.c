//#include "telag.h"
#include "arvore.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Arv cria_arv(char *palavra){
    Arv arv = malloc(sizeof(struct arv));
    arv->palavra = strdup(palavra);
    arv->alt = 0;
    arv->largura = strlen(palavra);
    arv->dir = arv->esq = NULL;
    arv->x = 0;
    arv->y = 0;
    return arv;
}
void printa_arv(Arv base, int espaco) {
    if (base == NULL) return;

    // Aumenta a distância entre níveis
    espaco += 10;

    // Imprime a subárvore direita
    printa_arv(base->dir, espaco);

    // Imprime o nó atual após o espaço adequado
    printf("\n");
    for (int i = 10; i < espaco; i++) {
        printf(" ");
    }
    printf("%s\n", base->palavra);

    // Imprime a subárvore esquerda
    printa_arv(base->esq, espaco);
}

Arv insere_arv(Arv base, char *palavra){
    printf("VERIFICA\n");
    if(base == NULL) return cria_arv(palavra);
    printf("PASSOU1\n");
    if(strcmp(base->palavra, palavra)>0){
        printf("ESQUERDA\n");
        base->esq = insere_arv(base->esq, palavra);
    }
    else if(strcmp(base->palavra, palavra)<0){
        printf("DIREITA\n");
        base->dir = insere_arv(base->dir, palavra);
    }
    printf("PASSOU2\n");
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