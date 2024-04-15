#include "esparsa.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int n_lin = 5;
    int n_col = 5;
    Esparsa *e = cria_esparca(n_lin, n_col);
    for(int i = 0; i<n_lin; i++){
        insere_esparca(e, (i+1)*2, i, i);
    }
    insere_esparca(e, 4, 1, 2);
    imprime_esparca(e);
    consulta_esparca(e, 4, 4);
    int linha_soma;
    printf("Insira a linha para somar todos os valores dela: ");
    scanf("%d", &linha_soma);
    soma_linha(e, linha_soma);
    float perc = percentual(e);
    printf("Percentual de dados nao nulos da matriz = %.2f%%\n", perc);
    return 0;
}