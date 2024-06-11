#include "arvore.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    arv_t *a = cria_no_vazio(); // ou poderia ser arv_cria(), pra ficar como os TAD vistos antes
    insere(a, "abc");
    printa_arv(a, 0);
    insere(a, "aab");
    printa_arv(a, 0);
    insere(a, "bbc");
    printa_arv(a, 0);
    dado_t b = busca(a, "aab");
    printf("\n\n\n %s\n", b->palavra);
    remove_no(a, "bbc");
    printa_arv(a, 0);
    return 0;
}
