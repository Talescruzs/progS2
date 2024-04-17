#ifndef _IDENTIDADE_H_
#define _IDENTIDADE_H_

struct matriz {
    int ordem;
    int n_elementos;
    struct linha* linha;
};
typedef struct matriz Mat;
struct linha {
    struct item* ini;
    struct linha* proxL;
};
typedef struct linha Lin;

struct item {
    int info;
    struct item* prox;
};
typedef struct item Item;

Mat *cria_matriz(int ordem);
void popula_matriz(Mat* self, int val);
void imprime_matriz(Mat* self);
int verifica_identidade(Mat* self);



#endif
