#include "diagonal.h"
#include <stdlib.h>
#include <stdio.h>

Diagonal *cria_matriz(int ordem){
    Diagonal *self = malloc(sizeof(Diagonal));
    if (self == NULL) return NULL;
    self->v = (int*)malloc(ordem * sizeof(int));
    if (self->v == NULL) {
        free(self);
        return NULL;
    }

    self->ordem = ordem;
    return self;
}
void preenche_matriz_manual(Diagonal *self, int val, int pos){
    self->v[pos] = val; 
}
void preenche_matriz_automatico(Diagonal *self){
    for(int i=0; i<self->ordem; i++){
        self->v[i] = i+1; 
    }
}

int consulta_elemento_matriz(Diagonal *self, int linha, int coluna){
    if(linha!=coluna){
        return 0;
    }
    else{
        return self->v[linha];
    }
}

void imprime_matriz(Diagonal *self){
    int elemento;
    printf("\nImprimindo a matriz\n");
    for(int i = 0; i<self->ordem; i++){
        for(int j=0; j<self->ordem; j++){
            elemento = consulta_elemento_matriz(self, i, j);
            printf("%d  ", elemento);
        }
        printf("\n");
    }
    printf("----------------------\n");
}