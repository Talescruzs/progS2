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
Fila fila_cria(int tam_do_dado) {
  int qtd_inicial = 10;
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

  return pos_v%self->cap;
}
static int converte_ponteiro_positivo(Fila self, int pos){

  if(pos>=self->n_elem){
    return -1;
  }  // pediu posicao alem da quantidade de elementos inseridos

  int pos_v = (self->ini+pos);

  return (pos_v)%self->cap;
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
  int pos_r = converte_ponteiro(self, pos);
  if(pos_r == -1){
    return NULL;
  } 
  void *ptr = (char *)self->espaco + (pos_r * self->tam_dado);

  return ptr;
}

bool fila_vazia(Fila self) { 
  return self->n_elem == 0; 
}

static void corta_lista(Fila self){
  void *ptrVelho, *ptrNovo;
  int qtdPart;
  if(self->ini>=self->cap/2) {
      ptrVelho = calcula_ponteiro(self, 0);
      self->ini/=2;
      ptrNovo = calcula_ponteiro(self, self->ini);
      qtdPart = self->cap - self->ini;
      memmove(ptrNovo, ptrVelho, qtdPart*self->tam_dado);
  }
  else{
    if(self->n_elem+self->ini>=self->cap/2){
      // qtdPart = (self->cap-(self->n_elem+self->ini))*(-1);
      // qtdPart = self->n_elem-self->ini;
      qtdPart = self->n_elem+self->ini-self->cap;
      ptrVelho = calcula_ponteiro(self, qtdPart);
      self->cap/=2;
      ptrNovo = calcula_ponteiro(self, -qtdPart);
      
      memmove(ptrNovo, ptrVelho, qtdPart*self->tam_dado);
    }
  }
  self->espaco = realloc(self->espaco, (self->tam_dado)*(self->cap)/2);
  assert(self->espaco!=NULL);
}


void fila_remove(Fila self, void *pdado) { //ainda precisa de melhora
  void *ptr = calcula_ponteiro(self, 0);
  assert(ptr != NULL); 
  if (pdado != NULL) {
    memmove(pdado, ptr, self->tam_dado);
  }
  self->n_elem--;
  if(self->ini<self->cap-1){
    self->ini++;
  } 
  else self->ini = 0;

  if(self->n_elem<=(self->cap/3)){
    corta_lista(self);
  }
}

static void dobra_fila(Fila self){ // calcular pos final depois de mudar o ini e a cap, daí compara e vê se faz a troca
  self->espaco = realloc(self->espaco, (self->tam_dado)*(self->cap)*2);
  assert(self->espaco!=NULL);
  
  void *ptrVelho, *ptrNovo;
  int qtdPart;

  if(self->ini>=self->cap/2) { //inicio dps da metade do vetor
    ptrVelho = calcula_ponteiro(self, 0); // inicio na fila
    qtdPart = self->cap-self->ini; // n elementos para mexer
    self->cap*=2;
    ptrNovo = calcula_ponteiro(self, -qtdPart);
    memmove(ptrNovo, ptrVelho, qtdPart*self->tam_dado);
    self->ini = self->cap - qtdPart -1;
  }
  else{
    int qtdPart = (self->ini+self->n_elem)%self->cap;
    ptrVelho = calcula_ponteiro(self, self->cap-self->ini);
    self->cap*=2;
    ptrNovo = calcula_ponteiro(self, self->ini+self->n_elem-qtdPart);
    memmove(ptrNovo, ptrVelho, qtdPart*self->tam_dado);
  }
}



void fila_insere(Fila self, void *pdado) { //ainda precisa de melhora
  self->n_elem++;
  if(self->n_elem >= self->cap){
    dobra_fila(self);
  }
  void *ptr = (char*)calcula_ponteiro(self, -1);
  memmove(ptr, pdado, self->tam_dado);
}


void fila_inicia_percurso(Fila self, int pos_inicial) {
  self->pos_percurso = pos_inicial;
}

bool fila_proximo(Fila self, void *pdado){
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
