#include "identidade.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int ordem = 3;
    int valor = 0;
    int qtd_fora;

    printf("\n-------------------------\n");
    printf("--MATRIZ NAO IDENTIDADE--\n");
    printf("-------------------------\n\n");
    Mat* matriz_nao_identidade = cria_matriz(ordem);
    for(int i = 0; i<ordem; i++){
        for(int j = 0; j<ordem; j++){
            popula_matriz(matriz_nao_identidade, valor);
            valor++;
        }
    }
    imprime_matriz(matriz_nao_identidade);
    qtd_fora = verifica_identidade(matriz_nao_identidade);
    printf("Quantidade de numeros que estao fora da identidade: %d\n", qtd_fora);

    printf("\n-------------------------\n");
    printf("----MATRIZ IDENTIDADE----\n");
    printf("-------------------------\n\n");

    Mat* matriz_identidade = cria_matriz(ordem);
    for(int i = 0; i<ordem; i++){
        for(int j = 0; j<ordem; j++){
            if(i==j){
                popula_matriz(matriz_identidade, 1);
            }
            else{
                popula_matriz(matriz_identidade, 0);
            }
        }
    }
    imprime_matriz(matriz_identidade);
    qtd_fora = verifica_identidade(matriz_identidade);
    printf("Quantidade de numeros que estao fora da identidade: %d\n", qtd_fora);
    return 0;
}
