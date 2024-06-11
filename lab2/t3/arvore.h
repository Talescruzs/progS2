#ifndef _arvore_h_ 
#define _arvore_h_
typedef struct data{
    char *palavra;
    int x;
    int y;
} *dado_t;
typedef struct _no no_t;
struct _no {
    dado_t val;
    int largura;
    int alt;
    no_t *esq;
    no_t *dir;
};
typedef no_t arv_t;

int num_nos(arv_t *a);
int altura(arv_t *a);
arv_t *no(char *palavra, arv_t *esq, arv_t *dir);
arv_t *cria_no_vazio(void);
void insere(no_t *a, char *palavra);
void remove_no(arv_t *a, char *p);
void printa_arv(arv_t *base, int espaco);
dado_t busca(arv_t *a, char *palavra);

#endif
