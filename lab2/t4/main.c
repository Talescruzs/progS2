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
    grafo_remove_no(g, 1);
    printa_grafo(g);
    printf("ADD ARESTA\n");
    v_dado2 = 1.2;
    grafo_altera_valor_aresta(g, 1, 2, dado2);
    v_dado2 = 0.2;
    grafo_altera_valor_aresta(g, 0, 2, dado2);
    v_dado2 = 1.3;
    grafo_altera_valor_aresta(g, 1, 3, dado2);
    v_dado2 = 3.1;
    // grafo_altera_valor_aresta(g, 3, 1, dado2);
    v_dado2 = 1.0;
    grafo_altera_valor_aresta(g, 1, 0, dado2);
    printa_grafo(g);
    printf("MODIFICA ARESTA\n");
    v_dado2 = 3.2;
    grafo_altera_valor_aresta(g, 1, 0, dado2);
    printa_grafo(g);
    printf("REMOVENDO ARESTA\n");
    grafo_altera_valor_aresta(g, 1, 0, NULL);
    printa_grafo(g);

    grafo_valor_aresta(g, 1, 2, dado2);
    printf("Teste: %f\n", v_dado2);


    printf("CONSULTANDO ARESTA QUE CHEGAM EM 2\n");
    grafo_arestas_que_chegam(g, 2);
    int *v = (int*)malloc(sizeof(int));
    while(grafo_proxima_aresta(g, v, dado2)){
        int vizinho = *v;
        printf("chega de %d\n", vizinho);
        printf("peso %f\n", v_dado2);
    }

    printf("CONSULTANDO ARESTA QUE PARTEM DE 1\n");
    grafo_arestas_que_partem(g, 1);
    while(grafo_proxima_aresta(g, v, dado2)){
        int vizinho = *v;
        printf("vai para %d\n", vizinho);
        printf("peso %f\n", v_dado2);
    }
    printf("VERIFICA SE TEM CICLO\n");
    if(grafo_tem_ciclo(g)){
        printf("tem\n");
    }
    else{
        printf("nao tem\n");
    }

    printf("CONSULTANDO ORDEM TOPOLOGICA\n");
    Fila f = grafo_ordem_topologica(g);
    fila_inicia_percurso(f, 0);
    while(fila_proximo(f, dado)){
        printf("%d\n", v_dado);
    }



    grafo_destroi(g);
    return 0;
}