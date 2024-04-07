#include "diagonal.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int n_ordem = 3;
    Diagonal *d = cria_diagonal(n_ordem);
    for(int i = 0; i<n_ordem; i++){
        insere_diagonal(d, i*2, i);
    }
    imprime_diagonal(d);
    for(int i = 0; i<n_ordem; i++){
        consulta_diagonal(d, i, i);
    }
    consulta_diagonal(d, 1, 2);
    return 0;
}