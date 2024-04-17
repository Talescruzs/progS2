#include "esparsa.h"
#include <stdlib.h>
#include <stdio.h>


Esparsa *cria_matriz(int n_lin, int n_col){
    Esparsa *self = malloc(sizeof(Esparsa));
    if (self == NULL) return NULL;
    self->linhas = n_lin;
    self->colunas = n_col;

    return self;
}

void preenche_matriz(Esparsa *self, int val, int lin, int col){
    Lista *novo_l = malloc(sizeof(Lista));
    if(col>=self->colunas || lin>=self->linhas){
        printf("Esta posicao nao pertence a matriz\n");
        return;
    }
    else if (novo_l == NULL){
        printf("Erro na alocacao de memoria\n");
        return;
    }
    else if(val == 0){
        printf("Necessario inserir valores nao nulos\n");
        return;
    }
    novo_l->info = val;
    novo_l->coluna = col;
    novo_l->linha = lin;

    if (self->prim == NULL) {
        self->prim = novo_l;
        return;
    }

    Lista *l_ant = NULL;
    Lista *l = self->prim;

    while (l != NULL && (l->linha < lin || (l->linha == lin && l->coluna < col))) {
        l_ant = l;
        l = l->prox;
    }
    if (l_ant == NULL) {
        novo_l->prox = self->prim;
        self->prim = novo_l;
    } else {
        novo_l->prox = l;
        l_ant->prox = novo_l;
    }
}

void imprime_matriz(Esparsa *self){
    int i, j;
    Lista *l = self->prim;
    printf("\n---------------------\n");
    printf("-Imprimindo a matriz-\n");
    printf("---------------------\n");
    for(i = 0; i < self->linhas; i++){
        for(j = 0; j < self->colunas; j++){
            if(l != NULL && l->linha == i && l->coluna == j){
                printf("%d  ", l->info);
                l = l->prox;
            } else {
                printf("0  ");
            }
        }
        printf("\n");
    }
}

void consulta_elemento(Esparsa *self, int lin, int col){
    printf("\n----------------------\n");
    printf("-Consulta de elemento-\n");
    printf("----------------------\n");
    if(col>=self->colunas || lin>=self->linhas){
        printf("Posicao solicitada nao pertence a matriz\n");
    }
    Lista *l = self->prim;
    while(l->linha!=lin || l->coluna!=col){
        l = l->prox;
        if(l==NULL){
            printf("[%i][%i] = 0\n", lin, col);
            return;
        } 
    }
    printf("[%i][%i] = %i\n", lin, col, l->info);
}

void soma_linha(Esparsa *self, int lin){
    printf("\n-----------------------\n");
    printf("-Somatorio da linha %d-\n", lin);
    printf("-----------------------\n");
    int soma = 0;
    if(lin>=self->linhas){
        printf("Esta linha nao pertence a matriz\n");
    }
    Lista *l = self->prim;
    while(l!=NULL){
        if(l->linha == lin){
            soma+=l->info;
        }
        l = l->prox;
    }
    printf("somatorio = %i\n", soma);
}

float percentual(Esparsa *self){
    int cont = 0;
    int total = self->colunas*self->linhas;
    Lista *l = self->prim;
    while(l!=NULL){
        cont++;
        l = l->prox;
    }
    return (float) (cont*100)/total;
}
