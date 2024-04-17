#include "identidade.h"
#include <stdlib.h>
#include <stdio.h>

static Item *cria_item() {
    Item* item = (Item*)malloc(sizeof(Item));
    if(item == NULL) return NULL;
    item->prox = NULL;
    return item;
}

static Lin *cria_linha() {
    Lin* lin = (Lin*)malloc(sizeof(Lin));
    if(lin == NULL) return NULL;
    lin->ini = cria_item(); // Inicializa a lista de itens da linha
    if(lin->ini == NULL) {
        free(lin);
        return NULL;
    }
    lin->proxL = NULL;
    return lin;
}

void insere_item(Mat* self, int val) {
    Item* n_item = (Item*)malloc(sizeof(Item));
    if(n_item == NULL) {
        printf("Erro ao criar item\n");
        return;
    }

    n_item->prox = NULL;

    Lin *l = self->linha;
    while(l->proxL!=NULL){
        l=l->proxL;
    }
    Item *item = l->ini;
    while(item->prox!=NULL){
        item = item->prox;
    }
    item->info = val;
    item->prox = n_item;
}

void insere_linha(Mat* self) {
    Lin *n_linha = cria_linha();
    if(n_linha == NULL) {
        printf("Erro ao criar linha\n");
        return;
    }
    Lin *l = self->linha;
    while(l->proxL!=NULL){
        l=l->proxL;
    }
    l->proxL = n_linha;
}

Mat *cria_matriz(int ordem){
    Mat *self = malloc(sizeof(Mat));
    if (self == NULL) return NULL;
    
    self->linha = cria_linha();
    if (self->linha == NULL){
        free(self);
        return NULL;
    }
    self->linha->ini = cria_item();
    if (self->linha->ini == NULL){
        free(self->linha);
        free(self);
        return NULL;
    }
    self->ordem = ordem;
    self->n_elementos = 0;

    return self;
}

void popula_matriz(Mat* self, int val){
    if(self->n_elementos>(self->ordem*self->ordem)){
        printf("Posicao fora da matriz\n");
    }
    else{
        if(self->n_elementos%self->ordem == 0 && self->n_elementos!=0){ //linha cheia
            insere_linha(self);
        }
        insere_item(self, val);
        self->n_elementos++;
    }
}

void imprime_matriz(Mat* self){
    Lin *l = self->linha;
    while(l!=NULL){
        Item *i = l->ini;
        while(i->prox!=NULL){
            printf("%d  ", i->info);
            i = i->prox;
        }
        printf("\n");
        l = l->proxL;
    }
}

int verifica_identidade(Mat* self){
    int count_n_fora=0, count_linha=0, count_coluna=0;

    Lin *l = self->linha;
    while(l!=NULL){
        Item *i=l->ini;
        while(i->prox!=NULL){
            if(count_coluna!=count_linha){
                if(i->info!=0){
                    printf("Numero %d, em [%d][%d], viola a identidade\n", i->info, count_linha, count_coluna);
                    count_n_fora++;
                }
            }
            else if(i->info!=1){
                printf("Numero %d, em [%d][%d], viola a identidade\n", i->info, count_linha, count_coluna);
                count_n_fora++;
            }
            count_coluna++;
            i = i->prox;
        }
        l = l->proxL;
        count_linha++;
        count_coluna=0;
    }


    return count_n_fora;
}