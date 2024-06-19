#ifndef _arvore_h_ 
#define _arvore_h_
typedef struct dado{
    char palavra[10];
    int x;
    int y;
    int largura;
    int alt;
}Dado; 
struct arv{
    Dado *val;
    struct arv* esq;
    struct arv* dir;
};
typedef struct arv Arv;

void cria_palavra(char *palavra);

int arruma_altura(Arv *a);
Arv* cria_arv();
Arv* insere(Arv *a, char *palavra);
Arv* remover_no(Arv *a, char *p);
void printa_arv_velho(Arv *base, int espaco);

int calcula_x_arv(Arv *a, int ini);
void calcula_y_arv(Arv *a, int ini, int tam_letra);

void printa_arv(Arv *a);
Arv *busca(Arv *a, char *palavra);

#endif
