//#include "telag.h"
#include "arvore.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int vazia(arv_t *a){
    if(a->val == NULL) return 1;
    return 0;
}
int pega_maior(int a, int b){
    if(a>b) return a;
    return b;
}
int num_nos(arv_t *a){
    if (vazia(a)) return 0;
    return 1 + num_nos(a->esq) + num_nos(a->dir);
}
int altura(arv_t *a){
    if (vazia(a)) return -1;
    a->alt = 1 + pega_maior(altura(a->esq), altura(a->dir));
    return a->alt;
}
int menor(char *a, char *b){
    if(strcmp(a, b) < 0 ) return 0;
    return 1;
}
int iguais(char *a, char *b){
    if(strcmp(a, b) == 0 ) return 0;
    return 1;
}
arv_t *no(char *palavra, arv_t *esq, arv_t *dir){
    arv_t *n = (arv_t *)malloc(sizeof(arv_t));
    assert(n != NULL);
    dado_t d = (dado_t)malloc(sizeof(dado_t*));
    assert(d != NULL);
    d->palavra = palavra;
    n->val = d;
    n->esq = esq;
    n->dir = dir;
    return n;
}
arv_t *cria_no_vazio(void){
    no_t *n = malloc(sizeof(no_t));
    assert(n != NULL);
    // o valor nunca vai ser usado
    n->esq = NULL;
    n->dir = NULL;
    n->val = NULL;
    return n;
}
dado_t busca(arv_t *a, char *palavra){
    if (vazia(a)) return NULL;                             // o valor certamente não está em uma árvore vazia!
    if (iguais(palavra, a->val->palavra)) return (a->val);         // achei!
    if (menor(palavra, a->val->palavra)) return busca(a->esq, palavra);  // valor pequeno, retorna o resultado da busca na subárvore esquerda
    return busca(a->dir, palavra);                             // valor grande, continua pela direita
}

void insere(arv_t *a, char *p){
    dado_t d = (dado_t)malloc(sizeof(dado_t));
    assert(d != NULL);
    d->palavra = p;

    if (vazia(a)) {
        a->val = d;
        a->esq = cria_no_vazio();
        a->dir = cria_no_vazio();
    } else if (iguais(p, a->val->palavra)) {
        ; // ou reaje de outra forma para inserção de valor já existente
    } else if (menor(p, a->val->palavra)) {
        insere(a->esq, p);   // valor pequeno, insere na subárvore esquerda
    } else {
        insere(a->dir, p);   // valor grande, insere na subárvore direita
    }
}
int folha(arv_t *a){
    if(vazia(a->dir) && vazia(a->esq)) return 0;
    return 1;
}
void remove_no(arv_t *a, char *p){
    if (vazia(a)) {
        return;                     // arvore vazia não tem o dado, não faz nada
    } else if (iguais(p, a->val->palavra)) {
        if (folha(a)) {  // o caso fácil, transforma a em árvore vazia
        a->val = NULL;
        free(a->esq);  // libera o nó vazio
        free(a->dir);  // o outro também
        a->esq = a->dir = NULL; // para reconhecermos como nó vazio mais tarde
        } else {  // o caso menos fácil, o nó tem filho(s)!
        // TODO
        }
    } else if (menor(p, a->val->palavra)) {
        remove_no(a->esq, p);      // valor pequeno, remove da esquerda
    } else {
        remove_no(a->dir, p);      // valor grande, remove da direita
    }
}


void printa_arv(arv_t *a, int espaco) {
    if (vazia(a)) return;

    espaco += 10;

    printa_arv(a->dir, espaco);

    printf("\n");
    for (int i = 10; i < espaco; i++) {
        printf(" ");
    }
    printf("%s\n", a->val->palavra);

    printa_arv(a->esq, espaco);
}
