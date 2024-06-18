#include "arvore.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Arv *a = cria_arv();
    char teste [10];
    int i = 0;
    while(i<10){
        cria_palavra(teste);
        // printf("%s\n", teste);
        a = insere(a, teste);
        // printa_arv(a, 0);
        i++;
    }
    printa_arv(a, 0);
    return 0;
}
