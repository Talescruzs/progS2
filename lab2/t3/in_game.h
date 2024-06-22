#ifndef _in_game_h_ 
#define _in_game_h_

#include "arvore.h"
#include "telag.h"

// // tamanhos de tela para o jogo
// #define pequena 0
// #define media 1
// #define grande 2

typedef struct espaco{
    int iniX;
    int iniY;
    int tamX;
    int tamY;
} *Espaco;
typedef struct palavra{
    char proxima_palavra [10];
    char palavra_digitada [10];
    char letra_digitada; 
    int palavra_mudou;
    int tamanho_letra;
} *Palavra;
typedef struct relogio{
    double clock_total;
    double clock_utlima_mudanca;
    int tempo_aleatorio;
} *Relogio;
typedef struct jogo{
    Espaco tela_total;
    Espaco header;
    Espaco footer;
    Palavra palavras;
    Relogio relogio;
    Arv *arvore;

} *Jogo; 

Jogo cria_jogo();
Jogo jogoIni(int tam);
void jogoFim();

void remove_ultima_letra(char *p);
void seta_ultima_letra(char *p, char l, int tam);
int controle_palavra(double ini_temp, int demora);
void to_char(int n, char *palavra);

void cria_palavra(char *palavra);

#endif