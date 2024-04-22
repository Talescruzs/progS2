#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 1000

struct _fila {
  int tam_dado;
  int pos_percurso;
  void *espaco; //ponteiro para o dado em si
  struct _fila *prox;
};


// Dep depura(Fila self){
//   Dep d = malloc(sizeof(struct depurador));
//   d->cap = self->cap;
//   d->ini = self->ini;
//   d->n_elem = self->n_elem;
//   d->tam_dado = self->tam_dado;
//   d->pos_percurso = self->pos_percurso;
//   d->espaco = malloc(d->cap * d->tam_dado);
//   d->espaco = self->espaco;
//   return d;
// }
// funções que implementam as operações básicas de uma fila

// cria uma fila vazia que suporta dados do tamanho fornecido (em bytes)
Fila fila_cria(int tam_do_dado) { // implementado
  Fila self = malloc(sizeof(struct _fila));
  if (self != NULL) {
    self->espaco = malloc(tam_do_dado);

    if (self->espaco != NULL) {
      self->tam_dado = tam_do_dado;
    } 
    else {
      free(self);
      self = NULL;
    }
  }
  return self;
}

void fila_destroi(Fila self) {
    Fila prox = self->prox;
    while (prox != NULL) {
        Fila temp = prox;
        prox = prox->prox;
        free(temp);
    }
    free(self);
}


bool fila_vazia(Fila self) {  // implementado
  return self->prox == NULL; 
}

void fila_remove(Fila self, void *pdado) {

    if (self->prox == NULL) {
        return;
    }

    void *ptr = self->prox->espaco;
    assert(ptr != NULL);
    if (pdado != NULL) {
        memmove(pdado, ptr, self->tam_dado);
    }
    Fila proximo = self->prox;
    self->prox = proximo->prox;
    free(proximo);
}


void fila_insere(Fila self, void *pdado) { // a
  Fila f = self;
  while(f->prox!=NULL){
    f=f->prox;
  }
  Fila novo = fila_cria(self->tam_dado);
  memmove(novo->espaco, pdado, self->tam_dado);
  f->prox = novo;
}


void fila_inicia_percurso(Fila self, int pos_inicial) { // ok
  self->pos_percurso = pos_inicial;
}

bool fila_proximo(Fila self, void *pdado){ // ok
  void *ptr;
  Fila f = self;
  int count = 0;
  while(count<=self->pos_percurso){
    if(f->prox==NULL) return false;
    f=f->prox;
    count++;
  }
  ptr = f->espaco;
  if(ptr==NULL) return false;
  memmove(pdado, ptr, self->tam_dado);
  if (self->pos_percurso < 0) {
    self->pos_percurso--;
  } else {
    self->pos_percurso++;
  }
  return true;
}
