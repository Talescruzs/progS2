#include "arvore.h"
#include "telag.h"
#include "in_game.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    // Arv *a = cria_arv();
    Jogo j = jogoIni(0, 10, 1);
    
    char palavra_digitada [10];
    char letra_digitada;
    int eq;
    char fator_eq[3];
    int cor;

    while(1){
        verifica_tempo(j->relogio, 10);
        if(j->relogio->palavra_mudou){
            troca_palavra(j);
        }
        letra_digitada = tela_tecla();
        if(letra_digitada=='\n'){
            j->arvore = remover_no(j->arvore, palavra_digitada);
            palavra_digitada[0] = '\0';
        }
        else if(letra_digitada=='\b'){
            remove_ultima_letra(palavra_digitada);
        }
        else if(letra_digitada!=0){
            seta_ultima_letra(palavra_digitada, letra_digitada, 10);
        }
        arruma_altura(j->arvore);
        eq = fator_equilibrio(j->arvore);
        calcula_x_arv(j->arvore, 0);
        calcula_y_arv(j->arvore, 50, 30);
        printa_arv(j->arvore, j->max_equilibrio);
        to_char(eq, fator_eq);
        if(eq<j->max_equilibrio && eq>j->max_equilibrio*-1){
            cor = 8;
        }
        else if(eq==j->max_equilibrio || eq==j->max_equilibrio*-1){
            cor = 2;
        }
        else{
            break;
            // tela_texto(800,50,30,2, fator_eq);
            // TODO: tela de derrota
        }
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX,j->tela_total->iniY,30,cor, fator_eq);
        tela_texto(100,50,20,8,"proxima palavra:");
        tela_texto(100,50,20,8,"proxima palavra:");
        tela_texto(275,50,20,8,j->palavra->proxima_palavra);
        tela_texto(125,j->tela_total->tamY-j->tela_total->iniY,20,8,"palavra sendo escrita:");
        tela_texto(300,j->tela_total->tamY-j->tela_total->iniY,20,8,palavra_digitada);
        tela_atualiza();
    }
    tela_fim();
    return 0;
}
