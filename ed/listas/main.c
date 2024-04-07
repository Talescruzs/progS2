#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

int main (void)
{
    Lista* l;
    l = lst_cria();
    lst_imprime(l);
    l=lst_insere(l, 23);
    lst_imprime(l);
    l=lst_insere(l, 45);
    lst_imprime(l);
    printf("%d\n", busca (l, 45)->info);

    return 0;
}