#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
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
int grafo_insere_no(Grafo self, void *pdado){
    No *l_nos = self->nos;
    if(l_nos==NULL){
        l_nos= (No*)malloc(sizeof(No));
        l_nos->valor = (void *)malloc(self->tam_no);
        l_nos->valor = pdado;
        l_nos->numero = 1;
        self->nos = l_nos;
        return l_nos->numero;
    }
    while(l_nos->prox!=NULL){
        l_nos = l_nos->prox;
    }
    l_nos->prox = (No*)malloc(sizeof(No));
    No *novo = l_nos->prox;
    novo->valor = (void *)malloc(self->tam_no);
    novo->valor = pdado;
    novo->numero = l_nos->numero+1;
    
    return novo->numero;
}