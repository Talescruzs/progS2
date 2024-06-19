#include "arvore.h"
#include "telag.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
void remove_ultima_letra(char *p){
    // printf("b\n");
    for(int i=0; p[i]!='\0'; i++){
        // printf("a\n");
        if(p[i+1] == '\0'){
            p[i] = '\0';
        }
    }
}
void seta_ultima_letra(char *p, char l, int tam){
    // printf("b\n");
    for(int i=0; i<tam; i++){
        // printf("a\n");
        if(p[i] == '\0'){
            p[i] = l;
            p[i+1] = '\0';
            break;
        }
    }
}
int controle_palavra(double ini_temp, int demora){
    double temp_atual = tela_relogio();
    if(temp_atual >= (ini_temp)+demora){
        return 1;
    }
    return 0;
}
int main(){
    Arv *a = cria_arv();
    int tam_x = 1800, tam_y = 900;
    tela_inicio(tam_x, tam_y, "joguinho super legal");

    char proxima_palavra [10];
    char palavra_digitada [10];
    char letra_digitada;
    int tempo_aleatorio;
    double clock;
    int palavra_mudou = 0;
    clock = tela_relogio();
    tempo_aleatorio = rand()%10;
    cria_palavra(proxima_palavra);

    while(1){
        palavra_mudou = controle_palavra(clock, tempo_aleatorio);
        if(palavra_mudou){
            a = insere(a, proxima_palavra);
            cria_palavra(proxima_palavra);
            clock = tela_relogio();
            tempo_aleatorio = rand()%10;
        }
        letra_digitada = tela_tecla();
        if(letra_digitada=='\n'){
            a = remover_no(a, palavra_digitada);
            palavra_digitada[0] = '\0';
        }
        else if(letra_digitada=='\b'){
            remove_ultima_letra(palavra_digitada);
        }
        else if(letra_digitada!=0){
            seta_ultima_letra(palavra_digitada, letra_digitada, 10);
        }
        calcula_x_arv(a, 0);
        calcula_y_arv(a, 50, 30);
        printa_arv(a);
        tela_texto(100,50,20,8,"proxima palavra:");
        tela_texto(275,50,20,8,proxima_palavra);
        tela_texto(125,tam_y-50,20,8,"palavra sendo escrita:");
        tela_texto(300,tam_y-50,20,8,palavra_digitada);
        tela_atualiza();
    }
    tela_fim();
    return 0;
}
