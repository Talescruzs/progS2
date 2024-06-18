#include "arvore.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Arv *a = cria_arv(); // ou poderia ser arv_cria(), pra ficar como os TAD vistos antes
    a = insere(a, "f");
    a = insere(a, "d");
    a = insere(a, "e");
    a = insere(a, "c");
    a = insere(a, "h");
    a = insere(a, "g");
    a = insere(a, "i");
    printa_arv(a, 0);
    a = remover_no(a, "d");
    printa_arv(a, 0);
    printf("\n\n\n");
    char teste [10];
    int i = 0;
    while(i<1000){
        cria_palavra(teste);
        printf("%s\n", teste);
        i++;
    }
    return 0;
}
