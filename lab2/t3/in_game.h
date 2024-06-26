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
    char palavra [10];
    int tamanho_letra;
} *Palavra;
typedef struct input_p{
    char palavra_digitada [10];
    char letra_digitada; 
    int tamanho_letra;
    int tentou_remover;
} *Input_p;
typedef struct relogio{
    double clock_total;
    double clock_utlima_mudanca;
    int tempo_aleatorio;
    int palavra_mudou;
} *Relogio;
typedef struct jogo{
    Espaco tela_total;
    Espaco header;
    Espaco footer;
    Input_p input_p;
    Palavra prox_p;
    Relogio relogio;
    Arv *arvore;
    int max_equilibrio;
} *Jogo; 


void verifica_tempo(Relogio relogio, int tempo_max);
void controle_input(Jogo j);

void troca_palavra(Jogo j);

Jogo cria_jogo();
Jogo jogoIni(int tam, int temp_max, int max_eq);
void jogoFim();

void remove_ultima_letra(char *p);
void seta_ultima_letra(char *p, char l, int tam);
int controle_palavra(double ini_temp, int demora);
void to_char(int n, char *palavra);

void cria_palavra(char *palavra);

#endif