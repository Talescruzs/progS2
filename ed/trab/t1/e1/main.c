#include "diagonal.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int n_ordem = 3;
    int i=0,j=0;
    int elemento;
    printf("----------------------\n");
    printf("-preenchimento manual-\n");
    printf("----------------------\n");
    Diagonal *d1 = cria_matriz(n_ordem);
    for(i = 0; i<n_ordem; i++){
        preenche_matriz_manual(d1, (i*2)+1, i);
    }
    
    imprime_matriz(d1);
    
    printf("\nConsuta dos elemtentos da matriz um a um\n");
    for(i = 0; i<n_ordem; i++){
        for(j=0; j<n_ordem; j++){
            elemento = consulta_elemento_matriz(d1, i, j);
            printf("%d  ", elemento);
        }
        printf("\n");
    }
    printf("----------------------\n");

    printf("\n--------------------------\n");
    printf("-preenchimento automatico-\n");
    printf("--------------------------\n");

    Diagonal *d2 = cria_matriz(n_ordem);
    preenche_matriz_automatico(d2);
    
    imprime_matriz(d2);

    printf("\nConsuta dos elemtentos da matriz um a um\n");
    for(i = 0; i<n_ordem; i++){
        for(j=0; j<n_ordem; j++){
            elemento = consulta_elemento_matriz(d2, i, j);
            printf("%d  ", elemento);
        }
        printf("\n");
    }
    printf("----------------------\n");

    return 0;
}