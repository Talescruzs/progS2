#ifndef _arvore_h_ 
#define _arvore_h_

typedef struct arv{
    struct arv *dir;
    struct arv *esq;
    char *palavra;
    int alt;
    int x;
    int y;
    int largura;
} *Arv;
Arv cria_arv(char *palavra);
Arv insere_arv(Arv base, char *palavra);
Arv remove_arv(Arv base, char *palavra);
void printa_arv(Arv base, int espaco);

#endif
