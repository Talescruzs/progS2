#include "identidade.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int ordem = 3;
    Mat* m = cria_matriz(ordem);
    for(int i = 0; i<ordem; i++){
        for(int j = 0; j<ordem; j++){
            insere_matriz(m, i+j, i, j);
        }
    }
    return 0;
}
