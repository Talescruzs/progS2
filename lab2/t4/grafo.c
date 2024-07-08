#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "grafo.h"

typedef struct aresta Ares;
// Lista de nós
typedef struct no {
    void *valor;
    int numero;
    Ares *arestas;
    struct no *prox;
} No;
// Lista de arestas
typedef struct aresta {
    void *peso;
    No *fim;
    struct aresta *prox;
} Aresta;

struct _grafo{
    No *nos;
    int tam_aresta;
    int tam_no;
};
No *cria_no(int numero, void *pdado, int tam_no){
    No* no = (No*)malloc(sizeof(No));
    no->valor = (void *)malloc(tam_no);
    memcpy(no->valor, pdado, tam_no);
    no->numero = numero;
    return no;
}
void printa_grafo(Grafo self){
    No *nos = self->nos;
    printf("Nos:\n");
    while(nos != NULL){
        No *temp = nos->prox;
        printf("Numero: %d\n", nos->numero);
        int *d = nos->valor;
        printf("Dado: %d\n", *d);
        Aresta *arestas = nos->arestas;
        if(arestas!=NULL){
            printf("Arestas:\n");
            while(arestas != NULL){
                Aresta *tempA = arestas->prox;
                printf("nada\n");
                arestas = tempA;
            }
        }
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
    while(nos != NULL){
        Aresta *arestas = nos->arestas;
        while(arestas != NULL){
            Aresta *temp = arestas->prox;
            free(arestas);
            arestas = temp;
        }
        No *temp = nos->prox;
        free(nos);
        nos = temp;
    }
    free(self);
}
int grafo_insere_no(Grafo self, void *pdado){
    if(self->nos==NULL){
        No *l_nos = cria_no(0, pdado, self->tam_no);
        self->nos = l_nos;
        return l_nos->numero;
    }
    No *l_nos = self->nos;
    while(l_nos->prox!=NULL){
        l_nos = l_nos->prox;
    }
    l_nos->prox = cria_no(l_nos->numero+1, pdado, self->tam_no);
    return l_nos->prox->numero;
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

    while(l_nos->prox != NULL && l_nos->numero<no){
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
void grafo_altera_valor_no(Grafo self, int no, void *pdado){
    if(self->nos==NULL) return;
    No *l_nos = self->nos;

    while(l_nos->prox != NULL && l_nos->numero<no){
        l_nos = l_nos->prox;
    }
    if(l_nos->numero!=no) return;
    memcpy(l_nos->valor, pdado, self->tam_no);
}
void grafo_valor_no(Grafo self, int no, void *pdado){
    if(self->nos==NULL) return;
    No *l_nos = self->nos;

    while(l_nos->prox != NULL && l_nos->numero<no){
        l_nos = l_nos->prox;
    }
    if(l_nos->numero!=no) return;
    memcpy(pdado, l_nos->valor, self->tam_no);
}
int grafo_nnos(Grafo self){
    if(self->nos == NULL) return 0;
    int count = 0;
    No *l_nos = self->nos;
    while(l_nos != NULL){
        l_nos=l_nos->prox;
        count++;
    }
    return count;
}