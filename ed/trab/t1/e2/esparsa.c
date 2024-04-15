#include "esparsa.h"
#include <stdlib.h>
#include <stdio.h>


Esparsa *cria_esparca(int n_lin, int n_col){
    Esparsa *self = malloc(sizeof(Esparsa));
    if (self == NULL) return NULL;
    
    self->prim = malloc(sizeof(Lista));
    if (self->prim == NULL){
        free(self);
        return NULL;
    }
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

void *insere_esparca(Esparsa *self, int val, int lin, int col){
    Lista *l = self->prim;
    if(col>=self->colunas || lin>=self->linhas){
        printf("Esta posicao nao pertence a matriz\n");
    }
    else if(val == 0){
        printf("Necessario inserir valores nao nulos");
    }
    else{
        while(l->prox!=NULL){
            l = l->prox;
        }
        l->prox = malloc(sizeof(Lista));
        if(l->prox == NULL){
            printf("Impossivel alocar mais posicoes :(\n");
        }
        else{
            l->info = val;
            l->coluna = col;
            l->linha = lin;
        }
    }
}

void imprime_esparca(Esparsa *self){
    Lista *l = self->prim;
    while(l->prox!=NULL) {
        printf("[%d][%d] = %d\n", l->linha, l->coluna, l->info);
        l = l->prox;
    }
}

void consulta_esparca(Esparsa *self, int lin, int col){
    if(col>=self->colunas || lin>=self->linhas){
        printf("Esta posicao nao pertence a matriz\n");
    }
    Lista *l = self->prim;
    while(l->linha!=lin || l->coluna!=col){
        l = l->prox;
        if(l==NULL){
            printf("Posicao nao existe na matriz\n");
            exit(0);
        } 
    }
    printf("[%i][%i] = %i\n", lin, col, l->info);
}

void soma_linha(Esparsa *self, int lin){
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
