#include "matriz3d.h"
#include <stdlib.h>
#include <stdio.h>

int* aloca_vet (int m){
    int* vet = (int*)malloc(sizeof(int*)*m);
    return vet;
}

int** aloca_matriz_basica (int m, int n){
    int** matriz = (int**)malloc(sizeof(int*)*n);
    if(matriz==NULL) return NULL;
    for(int i=0; i<n; i++){
        matriz[i] = aloca_vet(m);
        if(matriz[i] == NULL) return NULL;
    }
    return matriz;
}

int*** aloca_matriz (int m, int n, int z){
    int*** matriz = (int***)malloc(sizeof(int**)*z);
    if(matriz==NULL) return NULL;
    for(int i=0; i<z; i++){
        matriz[i] = aloca_matriz_basica(m, n);
        if(matriz[i] == NULL) return NULL;
    }
    return matriz;
}
void preenche_matriz (int m, int n, int z, int ***mat){
    int valor = 0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<z; k++){
                mat[i][j][k] = valor;
                valor++;
            }
        }
    }
}
void imprime_matriz (int m, int n, int z, int ***mat){
    for(int i=0; i<m; i++){
        printf("\n-----------------\n");
        printf("-corte numero %d-\n", i);
        printf("-----------------\n");
        for(int j=0; j<n; j++){
            for(int k=0; k<z; k++){
                printf("%d  ", mat[i][j][k]);
            }
            printf("\n");
        }
    }
}
