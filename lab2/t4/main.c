#include "grafo.h"
#include <stdio.h>

int main(){
    Grafo g = grafo_cria(sizeof(int), sizeof(float));
    int v_dado = 5;
    int *dado = &v_dado;
    int n_no;
    for(int i = 0; i<10; i++){
        n_no = grafo_insere_no(g, dado);
        printf("%d\n", n_no);
        v_dado++;
    }
    grafo_destroi(g);
    return 0;
}