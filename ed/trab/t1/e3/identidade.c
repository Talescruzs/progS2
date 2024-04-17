#include "identidade.h"
#include <stdlib.h>
#include <stdio.h>

struct List *cria_lista(int val) {
    struct List* item = (struct List*)malloc(sizeof(struct List));
    item->info = val;
    item->prox = NULL;
    return item;
}

// Função para criar uma nova linha
struct Lin* cria_linha() {
    struct Lin* lin = (struct Lin*)malloc(sizeof(struct Lin));
    lin->ini = NULL;
    lin->proxL = NULL;
    return lin;
}

Mat *cria_matriz(int ordem){
    Mat *self = malloc(sizeof(Mat));
    if (self == NULL) return NULL;
    
    self->linha = malloc(sizeof(Lin));
    if (self->linha == NULL){
        free(self);
        return NULL;
    }
    self->linha->ini = malloc(sizeof(List));
    if (self->linha->ini == NULL){
        free(self->linha);
        free(self);
        return NULL;
    }
    self->ordem = ordem;

    return self;
}

void insere_matriz(Mat* self, int val, int lin, int col){
    if(lin>=self->ordem || col>=self->ordem){
        printf("Posicao fora da matriz\n");
    }
    else{
        printf("aaaa\n");
        Lin *l = self->linha;
        for(int i=0; i<lin; i++){
            printf("linha %d\n", i);
            l = l->proxL;
        }
        List* item = l->ini;
        for(int i=0; i<col; i++){
            item = item->prox;
        }
        item->info = val;
    }
}
