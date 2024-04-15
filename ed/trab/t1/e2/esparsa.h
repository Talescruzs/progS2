#ifndef _ESPARSA_H_
#define _ESPARSA_H_

struct lista {
    int linha;
    int coluna;
    int info;
    struct lista* prox;
};
typedef struct lista Lista;

struct esparsa {
int linhas;
int colunas;
struct lista* prim;
};
typedef struct esparsa Esparsa;

Esparsa *cria_esparca(int n_lin, int n_col);

void *insere_esparca(Esparsa *self, int val, int lin, int col);

void imprime_esparca(Esparsa *self);

void consulta_esparca(Esparsa *self, int lin, int col);

void soma_linha(Esparsa *self, int lin);

float percentual(Esparsa *self);

#endif