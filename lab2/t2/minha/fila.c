#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 1000

// struct _fila {
//   int n_elem;
//   int tam_dado;
//   int pos_percurso;
//   void *espaco;
// };

struct _fila {
  int cap; //capacidade atual do vetor
  int ini; //posicao inicial do vetor circular
  int n_elem; //numero de elementos no vetor
  int tam_dado;
  int pos_percurso;
  void *espaco;
};

// funções que implementam as operações básicas de uma fila

// cria uma fila vazia que suporta dados do tamanho fornecido (em bytes)
Fila fila_cria(int tam_do_dado, int qtd_inicial) {
  Fila self = malloc(sizeof(struct _fila));
  if (self != NULL) {
    self->espaco = malloc(qtd_inicial * tam_do_dado);

    if (self->espaco != NULL) {
      self->n_elem = 0;
      self->ini = 0;
      self->cap = qtd_inicial;
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
  free(self->espaco);
  free(self);
}

static int converte_ponteiro_negativo(Fila self, int pos){
  int pos_v = self->ini+self->n_elem+pos;

  if(pos_v<0) return -1;

  if(pos_v>=self->cap){
    pos_v-=self->cap;
  }
  return pos_v;
}
static int converte_ponteiro_positivo(Fila self, int pos){
  int pos_v = self->ini+pos;

  if(pos_v>=self->ini+self->n_elem) return -1; // pediu posicao alem da quantidade de elementos inseridos

  if(pos_v>=self->cap){
    pos_v-=self->cap;
  }
  return pos_v;
}
static int converte_ponteiro(Fila self, int pos){ //converte da posicão na lista para uma posicao real no vetor
  int pos_v; 
  if(pos<0){
    pos_v = converte_ponteiro_negativo(self, pos);
  }
  else{
    pos_v = converte_ponteiro_positivo(self, pos);
  }
  return pos_v;
}
// calcula o valor do ponteiro para o elemento na posição pos da fila
static void *calcula_ponteiro(Fila self, int pos) {

  
  pos = converte_ponteiro(self, pos);
  if(pos == -1) return NULL;

  // TODO: suporte a pos negativa
  // if (pos < 0 || pos >= self->n_elem) return NULL;
  // calcula a posição convertendo para char *, porque dá para somar em
  //   bytes. tem que fazer essa conversão porque não conhecemos o tipo
  //   do dado do usuário, só o tamanho.
  void *ptr = (char *)self->espaco + pos * self->tam_dado;

  return ptr;
}

bool fila_vazia(Fila self) { 
  return self->n_elem == 0; 
}

static void corta_lista(Fila self){
  self->cap/=2;
  self->espaco = realloc(self->espaco, (self->tam_dado)*(self->cap));
  assert(self->espaco!=NULL);
}

void fila_remove(Fila self, void *pdado) { //ainda precisa de melhora
  void *ptr = calcula_ponteiro(self, 0);
  assert(ptr != NULL);
  if (pdado != NULL) {
    memmove(pdado, ptr, self->tam_dado);
  }
  ptr = calcula_ponteiro(self, 1);
  if (ptr != NULL) {
    // ptr aponta para o segundo elemento da fila
    //   (que vira o primeiro)
    // copia os dados que sobraram para o início do espaço
    //   (não precisaria fazer isso com vetor circular)
    memmove(self->espaco, ptr, self->tam_dado * (self->n_elem - 1));
  }
  self->n_elem--;

  // void *ptr = calcula_ponteiro(self, self->ini);
  // assert(ptr != NULL);
  // if (pdado != NULL) {
  //   memmove(pdado, ptr, self->tam_dado);
  // }
  // self->n_elem--;

  // if(self->n_elem<=(self->cap/4)){
  //   corta_lista(self);
  // }
}

static void dobra_fila(Fila self){
  self->espaco = realloc(self->espaco, (self->tam_dado)*(self->cap)*2);
  assert(self->espaco!=NULL);
  
  int i=0;
  void *ptrVelho, *ptrNovo;

  if(self->ini>=self->cap/2) {
    // ptrVelho = (char *)self->espaco + self->ini * self->tam_dado;
    // ptrNovo = (char *)self->espaco + self->cap * self->tam_dado;
    ptrVelho = calcula_ponteiro(self, 1);
    ptrNovo = calcula_ponteiro(self, -1)+1;
  }
  else{
    ptrVelho = (char *)self->espaco + self->ini + self->ini * self->tam_dado;
    ptrNovo = (char *)self->espaco + self->cap * self->tam_dado;
  }
  self->cap*=2;
}

void fila_insere(Fila self, void *pdado) { //ainda precisa de melhora
  // assert(self->n_elem < MAX_ELEM);
  // self->n_elem++;
  // void *ptr = calcula_ponteiro(self, self->n_elem - 1);
  // memmove(ptr, pdado, self->tam_dado);

  // assert(self->n_elem <= self->cap);
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
