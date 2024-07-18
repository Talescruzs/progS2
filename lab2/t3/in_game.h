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
typedef struct botao{
    Espaco esp;
    int retorno;
    char palavra[10];
    struct botao *prox; 
} *Botao;
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
    Botao bts;
    Arv *arvore;
    int max_equilibrio;
    int pontos;
    int dificuldade;
    int tam_letra;
    char jogador [10];
} *Jogo;


void verifica_tempo(Relogio relogio, int tempo_max);
void controle_input(Jogo j);

void troca_palavra(Jogo j);

Jogo cria_jogo();
void jogoIni(int temp_max, int max_eq, int dificuldade, Jogo j);
void jogoFim();

Jogo ini_tela();

void remove_ultima_letra(char *p);
void seta_ultima_letra(char *p, char l, int tam);
int controle_palavra(double ini_temp, int demora);
void cria_palavra(char *palavra);
void tela_menu(Jogo j);
void tela_jogo(Jogo j);
void tela_recordes(Jogo j);

void salva_recorde(char* jogador, int recorde, int dificuldade);

#endif