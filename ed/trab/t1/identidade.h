#ifndef _IDENTIDADE_H_
#define _IDENTIDADE_H_

struct matriz {
    int ordem;
    struct linha* linha;
};
typedef struct matriz Mat;
struct linha {
    struct lista* ini;
    struct linha* proxL;
};
typedef struct linha Lin;

struct lista {
    int info;
    struct lista* prox;
};
typedef struct lista List;

Mat *cria_matriz(int ordem);
void insere_matriz(Mat* self, int val, int lin, int col);



#endif
