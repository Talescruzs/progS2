#include "arvore.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Arv *a = cria_arv(); // ou poderia ser arv_cria(), pra ficar como os TAD vistos antes
    a = insere(a, "abc");
    // printa_arv(a, 0);
    a = insere(a, "aab");
    // printa_arv(a, 0);
    a = insere(a, "bbc");
    printa_arv(a, 0);
    a = remover_no(a, "bbc");
    printa_arv(a, 0);
    return 0;
}
