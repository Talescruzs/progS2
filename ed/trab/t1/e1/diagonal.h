#ifndef _DIAGONAL_H_
#define _DIAGONAL_H_

struct diagonal
{
    int ordem;
    int* v;
};
typedef struct diagonal Diagonal;

Diagonal *cria_matriz(int ordem);

void preenche_matriz_manual(Diagonal *self, int val, int pos);
void preenche_matriz_automatico(Diagonal *self);

void imprime_matriz(Diagonal *self);

int consulta_elemento_matriz(Diagonal *self, int linha, int coluna);

#endif