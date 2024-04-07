#ifndef _DIAGONAL_H_
#define _DIAGONAL_H_

struct diagonal
{
    int ordem; //ordem da matriz
    int* v; //o tamanho do vetor é igual a ordem da matriz. Os elementos da diagonal principal são armazenados neste vetor
};
typedef struct diagonal Diagonal;

Diagonal *cria_diagonal(int ordem);
void destroi_diagonal(Diagonal *self);

void insere_diagonal(Diagonal *self, int val, int pos);

void imprime_diagonal(Diagonal *self);

void consulta_diagonal(Diagonal *self, int linha, int coluna);

#endif