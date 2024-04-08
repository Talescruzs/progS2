#include "esparsa.h"
#include <stdlib.h>
#include <stdio.h>


Esparsa *cria_esparca(int n_lin, int n_col){
    Esparsa *self = malloc(sizeof(Esparsa));
    if (self == NULL) return NULL;
    
    // self->prim = malloc(sizeof(Lista));
    // if (self->prim == NULL){
    //     free(self);
    //     return NULL;
    // }
    self->linhas = n_lin;
    self->colunas = n_col;

    return self;
}
// static void destroi_lista(Lista *self){
//     while(self!=NULL){
//         Lista * l = self;
//         while(l->prox!=NULL){
//             l = l->prox;
//         }
//         free(l);
//     }
// }
// void destroi_esparca(Esparsa *self){
//     destroi_lista(self->prim);
//     free(self);
// }

Lista *insere_esparca(Esparsa *self, int val, int lin, int col){
    Lista *l = NULL;
    if(col>=self->colunas || lin>=self->linhas){
        printf("Esta posicao nao pertence a matriz");
        return self->prim;
    }
    l->info = val;
    l->coluna = col;
    l->linha = lin;
    l->prox=self->prim;
    self->prim = l;
    return l;
}
// Lista* lst_insere_ordenado (Lista* l, int v){
//     Lista* novo;
//     Lista* ant = NULL; /* ponteiro para elemento anterior */
//     Lista* p = l; /* ponteiro para percorrer a lista */
//     /* procura posição de inserção */
//     while (p != NULL && p->info < v)
//     { ant = p; p = p->prox; }
//     /* cria novo elemento */
//     novo = (Lista*) malloc(sizeof(Lista));
//     novo->info = v;
//     /* encadeia elemento */
//     if (ant == NULL)

//     { /* insere elemento no início */
//     novo->prox = l; l = novo; }
//     else { /* insere elemento no meio da lista */
//     novo->prox = ant->prox;
//     ant->prox = novo; }

//     return l;
// }

void imprime_esparca(Esparsa *self){
    Lista *l = self->prim;
    while(l->prox!=NULL) {
        printf("[%d][%d] = %d\n", l->linha, l->coluna, l->info);
        l = l->prox;
    }
}

// void consulta_esparca(Esparsa *self, int linha, int coluna);