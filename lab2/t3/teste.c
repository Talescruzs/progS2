#include "arvore.h"

int main(){
    Arv a = cria_arv("testea");
    Arv b = cria_arv("testeb");
    Arv c = cria_arv("cteste");
    Arv arvore = cria_arv("d");
    arvore = insere_arv(arvore, a);
    arvore = insere_arv(arvore, b);
    arvore = insere_arv(arvore, c);
    printa_arv(arvore);
    return 0;
}
