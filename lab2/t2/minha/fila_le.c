#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 1000

struct _fila {
  int tam_dado;
  int pos_percurso;
  void *espaco;
  _fila *prox;
  _fila *ant;
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
Fila fila_cria(int tam_do_dado) {
  Fila self = malloc(sizeof(struct _fila));
  if (self != NULL) {
    self->espaco = malloc(tam_do_dado);

    if (self->espaco != NULL) {
      self->prox = NULL;
      self->ant = NULL;
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
    Node* dado = self;
    while (dado != NULL) {
        Node* temp = dado;
        dado = dado->prox;
        free(temp);
    }
}


bool fila_vazia(Fila self) { 
  return self->prox == NULL; 
}

void fila_remove(Fila self, void *pdado) { 
  void *ptr = calcula_ponteiro(self, 0);
  assert(ptr != NULL); 
  if (pdado != NULL) {
    memmove(pdado, ptr, self->tam_dado);
  }
  self->n_elem--;
  if(self->ini>=self->cap-1){
    self->ini = 0;
  } 
  else self->ini++;

  if(self->n_elem<=(self->cap/4)){
    corta_lista(self);
  }
}

static void dobra_fila(Fila self){
  self->espaco = realloc(self->espaco, (self->tam_dado)*(self->cap)*2);
  assert(self->espaco!=NULL);
  
  void *ptrVelho, *ptrNovo;

  if(self->ini>=self->cap/2) {
    ptrVelho = calcula_ponteiro(self, 0); // inicio na fila
    int qtdPart = self->cap-self->ini; // n elementos para mexer
    ptrNovo = calcula_ponteiro(self, self->cap - self->ini);
    self->cap*=2;
    memmove(ptrNovo, ptrVelho, qtdPart*self->tam_dado);
    self->ini = self->cap - qtdPart;
  }
  else{
    ptrVelho = calcula_ponteiro(self, self->cap-(self->n_elem+self->ini));
    ptrNovo = (char *)calcula_ponteiro(self, self->cap-(self->n_elem+self->ini)-1);
    int qtdPart = (self->cap-(self->n_elem+self->ini))*(-1);
    self->cap*=2;
    memmove(ptrNovo, ptrVelho, qtdPart*self->tam_dado);
  }
}

void fila_insere(Fila self, void *pdado) { //ainda precisa de melhora
  if(self->n_elem >= self->cap){
    dobra_fila(self);
  }
  self->n_elem++;
  void *ptr = calcula_ponteiro(self, -1);
  memmove(ptr, pdado, self->tam_dado);
}


void fila_inicia_percurso(Fila self, int pos_inicial) {
  self->pos_percurso = pos_inicial;
}

bool fila_proximo(Fila self, void *pdado)
{
  void *ptr = calcula_ponteiro(self, self->pos_percurso);
  if (ptr == NULL) return false;
  memmove(pdado, ptr, self->tam_dado);
  if (self->pos_percurso < 0) {
    self->pos_percurso--;
  } else {
    self->pos_percurso++;
  }
  return true;
}
