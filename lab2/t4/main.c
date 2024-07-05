#include "grafo.h"
#include <stdio.h>

int main(){
    Grafo g = grafo_cria(sizeof(int), sizeof(float));
    int v_dado = 5;
    int *dado = &v_dado;
    int n_no;
    grafo_remove_no(g, v_dado);
    printa_grafo(g);
    printf("Começa inserir\n");
    for(int i = 0; i<10; i++){
        n_no = grafo_insere_no(g, dado);
        printf("%d\n", n_no);
        v_dado++;
        printa_grafo(g);
    }
    // v_dado = 1;
    printf("Começa remover\n");
    for(int i = 0; i<6; i++){
        grafo_remove_no(g, i);
        printa_grafo(g);
    }
    printf("AAAA\n");
    grafo_destroi(g);
    return 0;
}