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
// void destroi_esparca(Esparsa *self);

Lista *insere_esparca(Esparsa *self, int val, int lin, int col);

void imprime_esparca(Esparsa *self);

void consulta_esparca(Esparsa *self, int linha, int coluna);

#endif