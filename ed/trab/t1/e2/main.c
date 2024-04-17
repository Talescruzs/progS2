#include "esparsa.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int n_lin = 5;
    int n_col = 5;
    Esparsa *e = cria_matriz(n_lin, n_col);

    // for(int i = 0; i<n_lin; i++){
    //     preenche_matriz(e, (i+1)*2, i, i);
    // }
    preenche_matriz(e, 4, 0, 0);
    preenche_matriz(e, 3, 1, 0);
    preenche_matriz(e, 2, 0, 4);
    preenche_matriz(e, 7, 3, 1);
    preenche_matriz(e, 9, 0, 2);
    preenche_matriz(e, 4, 4, 0);
    // preenche_matriz(e, 0, 1, 1);
    imprime_matriz(e);
    consulta_elemento(e, 0, 2);
    int linha_soma = 0;
    // printf("Insira a linha para somar todos os valores dela: ");
    // scanf("%d", &linha_soma);
    soma_linha(e, linha_soma);
    float perc = percentual(e);
    printf("\n-Percentual de dados nao nulos da matriz = %.2f%%\n", perc);
    return 0;
}