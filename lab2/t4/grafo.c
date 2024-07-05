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

void printa_grafo(Grafo self){
    No *nos = self->nos;
    Aresta *arestas = self->arestas;
    printf("Arestas:\n");
    while(arestas != NULL){
        Aresta *temp = arestas->prox;
        printf("nada\n");
        arestas = temp;
    }
    printf("Nos:\n");
    while(nos != NULL){
        No *temp = nos->prox;
        printf("%d\n", nos->numero);
        nos = temp;
    }
}

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
        l_nos->numero = 0;
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
void grafo_remove_no(Grafo self, int no){
    if(self->nos==NULL) return;

    No *l_nos = self->nos;
    No *no_ant = self->nos;
    if(no == 0){
        self->nos = l_nos->prox;
        free(l_nos);
        while(no_ant != NULL){
            no_ant->numero --;
            no_ant = no_ant->prox;
        }
        return;
    }

    while(l_nos->numero<no && l_nos != NULL){
        no_ant = l_nos;
        l_nos = l_nos->prox;
    }
    if(l_nos->numero!=no) return;
    no_ant->prox = l_nos->prox;
    free(l_nos);
    no_ant = no_ant->prox;
    while(no_ant != NULL){
        no_ant->numero --;
        no_ant = no_ant->prox;
    }
}