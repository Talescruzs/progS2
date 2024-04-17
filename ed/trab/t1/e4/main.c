#include "matriz3d.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    int x=3, y=3, z=3;
    int ***matriz;
    matriz = aloca_matriz (x, y, z);
    if(matriz==NULL){
        printf("Nao foi possivel alocar a matriz\n");
        return 1;
    }
    preenche_matriz (x, y, z, matriz);
    imprime_matriz (x, y, z, matriz);

    return 0;
}
