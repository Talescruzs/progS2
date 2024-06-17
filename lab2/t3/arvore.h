#ifndef _arvore_h_ 
#define _arvore_h_
typedef struct dado{
    char *palavra;
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
int arruma_altura(Arv *a);
Arv* cria_arv();
Arv* insere(Arv *a, char *palavra);
Arv* remover_no(Arv *a, char *p);
void printa_arv(Arv *base, int espaco);
Arv *busca(Arv *a, char *palavra);

#endif
