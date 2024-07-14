#include "grafo.h"
#include <stdio.h>

int main(){
    Grafo g = grafo_cria(sizeof(int), sizeof(float));
    int v_dado = 5;
    int *dado = &v_dado;
    float v_dado2 = 5.5;
    float *dado2 = &v_dado2;
    grafo_remove_no(g, v_dado);
    printa_grafo(g);
    printf("Começa inserir\n");
    for(int i = 0; i<5; i++){
        grafo_insere_no(g, dado);
        v_dado++;
    }
    printa_grafo(g);
    grafo_valor_no(g, 3, dado);
    printf("valor de 3: %d\n", *dado);
    v_dado = 1;
    printf("MUDA\n");
    grafo_altera_valor_no(g, 3, dado);
    grafo_valor_no(g, 3, dado);
    printf("valor de 3: %d\n", *dado);
    printa_grafo(g);
    printf("Começa remover\n");
    for(int i = 0; i<2; i++){
        grafo_remove_no(g, i);
    }
    printa_grafo(g);
    printf("ADD ARESTA\n");
    grafo_altera_valor_aresta(g, 1, 2, dado2);
    grafo_altera_valor_aresta(g, 1, 0, dado2);
    printa_grafo(g);

    grafo_destroi(g);
    return 0;
}