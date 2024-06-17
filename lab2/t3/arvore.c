//#include "telag.h"
#include "arvore.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
//  internas
int vazia(Arv *a){
    if(a == NULL) return 1;
    return 0;
}
int folha(Arv *a){
    if(vazia(a->dir) && vazia(a->esq)) return 0;
    return 1;
}
int pega_maior(int a, int b){
    if(a>b) return a;
    return b;
}
int menor(char *a, char *b){
    // printf("%s  -   %s\n", a, b);
    // printf("%d\n", strcmp(a, b));
    if(strcmp(a, b) < 0 ) return 1;
    return 0;
}
int maior(char *a, char *b){
    if(strcmp(a, b) > 0 ) return 0;
    return 1;
}
int iguais(char *a, char *b){
    if(strcmp(a, b) == 0 ) return 0;
    return 1;
}
// relativas aos dados:
Dado *cria_dado(char *palavra){
    Dado *d = (Dado *)malloc(sizeof(Dado));
    assert(d != NULL);
    d->palavra = palavra;
    d->largura = strlen(palavra);
    return d;
}
int arruma_altura(Arv *a){
    if (vazia(a)) return -1;
    a->val->alt = 1 + pega_maior(arruma_altura(a->esq), arruma_altura(a->dir));
    return a->val->alt;
}
// relativas as arvores:
Arv* cria_arv(){
    return NULL;
}
Arv *busca(Arv *a, char *palavra){
    if (menor(palavra, a->val->palavra)) return busca(a->esq, palavra);
    if (menor(a->val->palavra, palavra)) return busca(a->dir, palavra);
    return a;
}
Arv *insere(Arv *a, char *p) {
    if (vazia(a)) {
        a = (Arv *)malloc(sizeof(Arv));
        assert(a!=NULL);
        Dado *d = cria_dado(p);
        a->val = d;
        a->esq = a->dir = NULL;
    } else if (menor(p, a->val->palavra)) {
        a->esq = insere(a->esq, p);   // valor pequeno, insere na subárvore esquerda
    } else {
        a->dir = insere(a->dir, p);   // valor grande, insere na subárvore direita
    }
    return a;
}
Arv *remover_no(Arv *a, char *v){
    if (vazia(a)) return NULL;
    else if (menor(v, a->val->palavra)){
        a->esq = remover_no(a->esq, v);
    }
    else if (menor(a->val->palavra, v)){
        a->dir = remover_no(a->dir, v);
    }
    else {
        if(vazia(a)){
            free(a);
            return NULL;
        } else if (a->esq == NULL){
            Arv* t = a;
            a = a->dir;
            free(t);
        } else if (a->dir == NULL){
            Arv* t = a;
            a = a->esq;
            free(t);
        } else{
            Arv* f = a->esq; // vai para a SAE
            while (f->dir != NULL) // busca o filho + à direita
            f = f->dir;
            Dado *d = a->val; 
            a->val = f->val; // troca os valores
            f->val = d;
            a->esq = remover_no(a->esq, v); // remove v
        }
    }
    return a;
}
void printa_arv(Arv *a, int espaco) {
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
