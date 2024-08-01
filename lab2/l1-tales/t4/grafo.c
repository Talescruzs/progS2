#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grafo.h"

typedef struct aresta Ares;
// Lista de nós
typedef struct no {
    void *valor;
    int numero;
    int visita;
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

typedef struct guarda_no {
    No *no;
    struct guarda_no *prox;
} Guarda_no;

struct _grafo{
    Consulta *consulta;
    // Guarda_no *guarda_no;
    No *nos;
    int tam_aresta;
    int tam_no;
    bool tem_ciclo;
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
    no->visita = 0;
    no->prox = NULL;
    no->arestas = NULL;
    return no;
}
void printa_grafo(Grafo self){
    No *nos = self->nos;
   printf("Nos:\n");
    while(nos != NULL){
        No *temp = nos->prox;
       printf(" Numero: %d\n", nos->numero);
        // int *d = nos->valor;
        // printf("Dado: %d\n", *d);
        Aresta *arestas = nos->arestas;
        if(arestas!=NULL){
           printf("  Arestas:\n");
            while(arestas != NULL){
                Aresta *tempA = arestas->prox;
                float *p = arestas->peso;
               printf("   De %d a %d com peso %f\n", arestas->origem, arestas->destino, *p);
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
    g->tem_ciclo = false;
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

void remove_aresta(int destino, No *origem);
void grafo_remove_no(Grafo self, int no){
    if(self->nos==NULL) return;
    Consulta *c = self->consulta;

    No *l_nos = self->nos;
    No *no_ant = self->nos;
    if(no == 0){
        self->nos = l_nos->prox;
        grafo_arestas_que_chegam(self, no);
        while(self->consulta!=NULL){
            c=self->consulta;
            remove_aresta(no, pega_no(self, c->aresta->origem));
            self->consulta = self->consulta->prox;
            free(c);
        }
        grafo_arestas_que_partem(self, no);
        while(self->consulta!=NULL){
            c=self->consulta;
            remove_aresta(no, pega_no(self, c->aresta->origem));
            self->consulta = self->consulta->prox;
            free(c);
        }
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
    grafo_arestas_que_chegam(self, no);
    while(self->consulta!=NULL){
        c=self->consulta;
        remove_aresta(no, pega_no(self, c->aresta->origem));
        self->consulta = self->consulta->prox;
        free(c);
    }
    grafo_arestas_que_partem(self, no);
    while(self->consulta!=NULL){
        c=self->consulta;
        remove_aresta(no, pega_no(self, c->aresta->origem));
        self->consulta = self->consulta->prox;
        free(c);
    }
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
    aresta->prox = NULL;
    aresta->fim = NULL;
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
    if(l_arestas==NULL) return;
    if(l_arestas->destino == destino){
        origem->arestas = origem->arestas->prox;
        free(l_arestas);
        return;
    }
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

Consulta *cria_consulta(Aresta *a, bool origem){
    Consulta* consulta = (Consulta*)malloc(sizeof(Consulta));
    consulta->aresta = a;
    consulta->prox = NULL;
    consulta->origem = origem;
    return consulta;
}
void destroi_consulta(Grafo self);
void insere_consulta(Grafo self, Aresta *a, bool origem){
    if(a == NULL){
        return;
    }
    if(self->consulta == NULL){
        self->consulta = cria_consulta(a, origem);
    }
    else{
        Consulta *c = self->consulta;
        while(c->prox!= NULL){
            c = c->prox;
        }
        c->prox = cria_consulta(a, origem);
    }

}

void destroi_consulta(Grafo self){
    Consulta *c = self->consulta;
    while(self->consulta!= NULL){
        c = self->consulta;
        self->consulta = self->consulta->prox;
        free(c); 
    }
}

void grafo_arestas_que_partem(Grafo self, int origem){
    destroi_consulta(self);
    No *n = pega_no(self, origem);
    Aresta *a = n->arestas;
    while(a!=NULL){
        insere_consulta(self, a, true);
        a = a->prox;
    }
}

void grafo_arestas_que_chegam(Grafo self, int destino){
    destroi_consulta(self);
    No *n = self->nos;
    while(n!=NULL){
        Aresta *a = n->arestas;
        while(a!=NULL){
            if(a->destino == destino){
                insere_consulta(self, a, false);
            }
            a=a->prox;
        }
        n=n->prox;
    }
}

bool grafo_proxima_aresta(Grafo self, int *vizinho, void *pdado){
    Consulta *c = self->consulta;
    if(c==NULL){
        return false;
    }
    if(c->origem == true){
        *vizinho = c->aresta->destino;
    }
    else{
        No *n = pega_no(self, c->aresta->origem);
        *vizinho = n->numero;
    }
    memmove(pdado, c->aresta->peso, self->tam_aresta);
    self->consulta = self->consulta->prox;
    free(c);
    return true;
}

void busca_profundidade(Grafo self, No *atual){
    if(atual->arestas == NULL){
        atual->visita = 2; //visitado
        return;
    }
    Aresta *l_arestas = atual->arestas;
    while(l_arestas!=NULL && !self->tem_ciclo){
        if(l_arestas->fim->visita==1){
            l_arestas->fim->visita = 3; // problema
            self->tem_ciclo = true;
            return;
        }
        else if(l_arestas->fim->visita==0){
            l_arestas->fim->visita = 1;
            busca_profundidade(self, l_arestas->fim);
        }
        l_arestas = l_arestas->prox;
    }
    atual->visita = 2; //visitado
}

bool todos_visitados(Grafo self){
    No *l_nos = self->nos;
    while(l_nos != NULL){
        if(l_nos->visita!=2) return false;
        l_nos = l_nos->prox;
    }
    return true;
}

bool grafo_tem_ciclo(Grafo self){
    No *l_nos = self->nos;
    while(l_nos != NULL && !todos_visitados(self)){
        if(l_nos->visita != 2) busca_profundidade(self, l_nos);
        if(self->tem_ciclo) return true;
        l_nos = l_nos->prox;
    }
    return false;
}

Guarda_no *cria_guarda_no(){
    Guarda_no* gn = (Guarda_no*)malloc(sizeof(Guarda_no));
    gn->no = NULL;
    gn->prox = NULL;
    return gn;
}

Guarda_no *insere_guarda_no(Guarda_no *self, No* n){
    if(self == NULL){
        self = cria_guarda_no();
        self->no = n;
        return self;
    }
    Guarda_no *gn = self;
    while(gn->prox!= NULL){
        gn = gn->prox;
    }
    gn->prox = cria_guarda_no();
    gn->prox->no = n;
    return self;
}

Guarda_no *remove_guarda_no(Guarda_no *self, int n){
    if(self->no == NULL){
        return NULL;
    }
    Guarda_no *gn = self;
    Guarda_no *ant = self;
    while(gn->prox!= NULL && gn->no->numero!=n){
        ant = gn;
        gn = gn->prox;
    }
    if(gn->no->numero==n){
        if(ant==gn){
            return gn->prox;
        }
        ant->prox = gn->prox;
        free(gn);
    }
    return self;
}

int qtd_restante_nos(Guarda_no *self){
    Guarda_no *gn = self;
    int count = 0;
    while(gn!=NULL){
        count++;
        gn = gn->prox;
    }
    return count;
}

Fila grafo_ordem_topologica(Grafo self){
    Fila fila = fila_cria(sizeof(int));
    No *l_nos = self->nos; 
    Guarda_no *gn = NULL;
    
    while(l_nos!=NULL){
        grafo_arestas_que_chegam(self, l_nos->numero);
        if(self->consulta == NULL){
            fila_insere(fila, &l_nos->numero); // antecessor de todos
        }
        else{
            gn = insere_guarda_no(gn, l_nos);
        }
        l_nos = l_nos->prox;
    }
    Guarda_no *temp = gn;
    int v_numero, v_n_no;
    int *numero = &v_numero;
    int *n_no = &v_n_no;
    float v_dado;
    float *dado = &v_dado;
    int flag = 0, add = 1;
    int mudou = 0;
    while(qtd_restante_nos(gn) > 0){
        l_nos = temp->no;

        grafo_arestas_que_chegam(self, l_nos->numero);

        while(grafo_proxima_aresta(self, numero, dado) && add==1){
            fila_inicia_percurso(fila, 0);
            while(fila_proximo(fila, n_no) && flag==0){
                if(v_n_no == v_numero){
                    flag = 1;
                }
            }
            if(flag==0){
                add = 0;
            }
            flag = 0;
        }
        if(add == 1){
            fila_insere(fila, &l_nos->numero); // antecessor de todos e sucessor apenas dos que já foram
            gn = remove_guarda_no(gn, l_nos->numero);
            mudou = 1;
        }

        temp = temp->prox;
        if(temp == NULL || temp->no==NULL){
            if(mudou == 0){
                fila_destroi(fila);
                fila = NULL;
                return fila;
            }
            else{
                temp = gn;
            }
        }
        mudou = 0;
        add = 1;
    }
    return fila;
}
