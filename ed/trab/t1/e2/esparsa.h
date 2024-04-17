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

Esparsa *cria_matriz(int n_lin, int n_col);

void preenche_matriz(Esparsa *self, int val, int lin, int col);

void imprime_matriz(Esparsa *self);

void consulta_elemento(Esparsa *self, int lin, int col);

void soma_linha(Esparsa *self, int lin);

float percentual(Esparsa *self);

#endif