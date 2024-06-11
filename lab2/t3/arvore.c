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

    espaco += 10;

    printa_arv(base->dir, espaco);

    printf("\n");
    for (int i = 10; i < espaco; i++) {
        printf(" ");
    }
    printf("%s\n", base->palavra);

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

Arv insere_galho(Arv base, Arv galho){
    printf("VERIFICA\n");
    if(base == NULL) return galho;
    printf("PASSOU1\n");
    if(strcmp(base->palavra, galho->palavra)>0){
        printf("ESQUERDA\n");
        base->esq = insere_arv(base->esq, galho->palavra);
    }
    else if(strcmp(base->palavra, galho->palavra)<0){
        printf("DIREITA\n");
        base->dir = insere_arv(base->dir, palavra);
    }
    printf("PASSOU2\n");
    return base;
}

Arv remove_arv(Arv base, char *palavra) {
    if (base == NULL) return NULL;

    if (strcmp(palavra, base->palavra) < 0) {
        base->esq = remove_arv(base->esq, palavra);
    } else if (strcmp(palavra, base->palavra) > 0) {
        base->dir = remove_arv(base->dir, palavra);
    } else {
        if (base->esq == NULL) {
            Arv temp = base->dir;
            free(base);
            return temp;
        } else if (base->dir == NULL) {
            Arv temp = base->esq;
            free(base->palavra);
            free(base);
            return temp;
        }

        // Nó com dois filhos
        Arv temp = min_valor_no(base->dir);
        free(base->palavra);
        base->palavra = strdup(temp->palavra);
        base->dir = remove_arv(base->dir, temp->palavra);
    }
    return base;
}