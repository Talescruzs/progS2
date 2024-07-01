#include <stdbool.h>
#include <assert.h>
#include "grafo.h"

// Lista de nós
typedef struct no {
    void *valor;
    int numero;
    struct no *prox;
} No;
// Lista de arestas
typedef struct aresta {
    void *peso;
    No *ini;
    No *fim;
    struct aresta *prox;
} Aresta;

struct _grafo{
    No *nos;
    Aresta *arestas;
    int tam_aresta;
    int tam_no;
};
Grafo grafo_cria(int tam_no, int tam_aresta) {
    Grafo g = (struct _grafo*)malloc(sizeof(struct _grafo));
    assert(g != NULL);
    g->tam_aresta = tam_aresta;
    g->tam_no = tam_no;
    return g;
}
void grafo_destroi(Grafo self){
    No *nos = self->nos;
    Aresta *arestas = self->arestas;
    while(arestas != NULL){
        Aresta *temp = arestas->prox;
        free(arestas);
        arestas = temp;
    }
    while(nos != NULL){
        No *temp = nos->prox;
        free(nos);
        nos = temp;
    }
    free(self);
}