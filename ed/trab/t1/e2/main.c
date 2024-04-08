#include "esparsa.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int n_lin = 5;
    int n_col = 5;
    Esparsa *e = cria_esparca(n_lin, n_col);
    for(int i = 0; i<n_lin; i++){
        e->prim = insere_esparca(e, i*2, i, 1);
    }
    imprime_esparca(e);
    // for(int i = 0; i<n_ordem; i++){
    //     consulta_diagonal(d, i, i);
    // }
    // consulta_diagonal(d, 1, 2);
    // destroi_esparca(e);
    return 0;
}