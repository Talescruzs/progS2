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
    int origem;
    int destino;
    No *fim;
    struct aresta *prox;
} Aresta;

typedef struct consulta {
    Aresta *aresta;
    bool origem;
    struct consulta *prox;
} Consulta;

struct _grafo{
    Consulta *consulta;
    No *nos;
    int tam_aresta;
    int tam_no;
};

No *pega_no(Grafo self, int id){
    No *l_nos = self->nos;
    while(l_nos!=NULL && l_nos->numero!=id){
        l_nos = l_nos->prox;
    }
    if(l_nos==NULL) return NULL;
    return l_nos;
} 
Aresta *pega_aresta(No *origem, int destino){
    Aresta *l_arestas = origem->arestas;
    while(l_arestas!=NULL && l_arestas->destino!=destino){
        l_arestas = l_arestas->prox;
    }
    if(l_arestas==NULL) return NULL;
    return l_arestas;
} 

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
                float *p = arestas->peso;
                printf("De %d a %d com peso %f\n", arestas->origem, arestas->destino, *p);
                arestas = tempA;
            }
        }
        nos = temp;
    }
}
Grafo grafo_cria(int tam_no, int tam_aresta) {
    Grafo g = (struct _grafo*)malloc(sizeof(struct _grafo));
    assert(g != NULL);
    g->consulta = NULL;
    g->nos = NULL;
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

Aresta *cria_aresta(void *peso, int tam_aresta){
    Aresta* aresta = (Aresta*)malloc(sizeof(Aresta));
    aresta->peso = (void *)malloc(tam_aresta);
    memcpy(aresta->peso, peso, tam_aresta);
    return aresta;
}
void insere_aresta(Grafo self, int destino, void *pdado, No *origem){
    if(self->nos == NULL) return;
    No *l_nos = self->nos;
    while(l_nos->prox != NULL && l_nos->numero<destino){
        l_nos = l_nos->prox;
    }
    if(l_nos->numero!=destino) return;

    Aresta *aresta = cria_aresta(pdado, self->tam_aresta);
    aresta->fim = l_nos;
    aresta->origem = origem->numero;
    aresta->destino = l_nos->numero;
    aresta->prox = NULL;

    Aresta *l_arestas = origem->arestas;
    if(l_arestas==NULL){
        origem->arestas = aresta;
        return;
    }
    while(l_arestas->prox!=NULL){
        l_arestas = l_arestas->prox;
    }
    l_arestas->prox = aresta;
}
void modifica_aresta(Aresta *aresta, void *pdado, int tam_aresta){
    memcpy(aresta->peso, pdado, tam_aresta);
}
void remove_aresta(int destino, No *origem){
    Aresta *l_arestas = origem->arestas;
    Aresta *ant = origem->arestas;
    while(l_arestas->prox != NULL && l_arestas->destino!=destino){
        ant = l_arestas;
        l_arestas = l_arestas->prox;
    }
    if(l_arestas->destino!=destino) return;
    ant->prox = l_arestas->prox;
    free(l_arestas);
}
void grafo_altera_valor_aresta(Grafo self, int origem, int destino, void *pdado){
    if(self->nos == NULL) return;
    No *l_nos = self->nos;
    while(l_nos->prox != NULL && l_nos->numero<origem){
        l_nos = l_nos->prox;
    }
    if(l_nos->numero!=origem) return;
    if(pdado!=NULL){
        Aresta * l_arestas = l_nos->arestas;
        while(l_arestas!=NULL && l_arestas->destino!=destino){
            l_arestas = l_arestas->prox;
        }
        if(l_arestas==NULL||l_arestas->destino!=destino){
            insere_aresta(self, destino, pdado, l_nos);
        }
        else{
            modifica_aresta(l_arestas, pdado, self->tam_aresta);
        }
    }
    else {
        remove_aresta(destino, l_nos);
    }
}

bool grafo_valor_aresta(Grafo self, int origem, int destino, void *pdado){
    No *l_nos = pega_no(self, origem);
    if(l_nos == NULL) return false;
    Aresta *aresta = pega_aresta(l_nos, destino);
    if(aresta == NULL) return false;
    memcpy(pdado, aresta->peso, self->tam_aresta);
    return true;
}

Consulta *cria_consulta(Aresta *a){
    Consulta* consulta = (Consulta*)malloc(sizeof(Consulta));
    consulta->aresta = a;
    consulta->prox = NULL;
    return consulta;
}

void insere_consulta(Grafo self, Aresta *a){
    if(self->consulta == NULL){
        self->consulta = cria_consulta(a);
        printf("Criou primeira consulta\n");
        return;
    }
    Consulta *c = self->consulta;
    while(c->prox!= NULL){
        c = c->prox;
    }
    c->prox = cria_consulta(a);
    printf("Criou proxima consulta\n");

}

void grafo_arestas_que_partem(Grafo self, int origem){
    No *n = pega_no(self, origem);
    Aresta *a = n->arestas;
    while(a!=NULL){
        insere_consulta(self, a);
        float *teste = (float*)a->peso;
        printf("inseriu %f\n", *teste);
        a = a->prox;
    }
    self->consulta->origem = true;
}

void grafo_arestas_que_chegam(Grafo self, int destino){
    No *n = self->nos;
    while(n!=NULL){
        Aresta *a = n->arestas;
        while(a!=NULL){
            if(a->destino == destino){
                insere_consulta(self, a);
                float *teste = (float*)a->peso;
                printf("inseriu %f\n", *teste);
            }
            a=a->prox;
        }
        n=n->prox;
    }
    self->consulta->origem = false;
}

bool grafo_proxima_aresta(Grafo self, int *vizinho, void *pdado){
    Consulta *c = self->consulta;
    if(c==NULL) return false;

    if(c->origem == true){
        printf("a\n");
        *vizinho = c->aresta->fim->numero;
    }
    else{
        No *n = pega_no(self, c->aresta->origem);
        *vizinho = n->numero;
    }
    memcpy(pdado, c->aresta->peso, self->tam_aresta);
    
    self->consulta = self->consulta->prox;
    free(c);
    return true;
}