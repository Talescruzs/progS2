#include "diagonal.h"
#include <stdlib.h>
#include <stdio.h>

Diagonal *cria_diagonal(int ordem){
    // aloca memória para o descritor
    Diagonal *self = malloc(sizeof(Diagonal));
    if (self == NULL) return NULL;
    // aloca memória para os dados
    self->v = malloc(ordem * sizeof(int));
    if (self->v == NULL) {
        free(self);
        return NULL;
    }
    
    self->ordem = ordem;
    return self;
}

void destroi_diagonal(Diagonal *self){
    free(self);
}

void insere_diagonal(Diagonal *self, int val, int pos){
    self->v[pos] = val; 
}

void imprime_diagonal(Diagonal *self){
    printf("Imprimindo Diagonal: \n");
    for(int i=0; i<self->ordem; i++){
        printf("[%d][%d] : %d\n", i,i,self->v[i]);
    }
    printf("-----------\n");
}

void consulta_diagonal(Diagonal *self, int linha, int coluna){
    if(linha!=coluna){
        printf("Posicao nao pertence a diagonal\n");
    }
    else{
        printf("%d\n", self->v[linha]);
    }
}