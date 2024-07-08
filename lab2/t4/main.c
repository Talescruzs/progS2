#include "grafo.h"
#include <stdio.h>

int main(){
    Grafo g = grafo_cria(sizeof(int), sizeof(float));
    int v_dado = 5;
    int *dado = &v_dado;
    grafo_remove_no(g, v_dado);
    printa_grafo(g);
    printf("Começa inserir\n");
    for(int i = 0; i<10; i++){
        grafo_insere_no(g, dado);
        printf("qtd nos: %d\n", grafo_nnos(g));
        v_dado++;
        // printa_grafo(g);
    }
    printa_grafo(g);
    v_dado = 1;
    grafo_altera_valor_no(g, 3, dado);
    grafo_valor_no(g, 2, dado);
    printf("valor de 2: %d\n", *dado);
    printa_grafo(g);
    printf("Começa remover\n");
    for(int i = 0; i<6; i++){
        grafo_remove_no(g, i);
        // printa_grafo(g);
    }
    // printf("AAAA\n");
    printa_grafo(g);
    grafo_destroi(g);
    return 0;
}