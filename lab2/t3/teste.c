#include "arvore.h"
#include "telag.h"
#include "in_game.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    Arv *a = cria_arv();
    int tam_x = 1800, tam_y = 900;
    tela_inicio(tam_x, tam_y, "joguinho super legal");

    char proxima_palavra [10];
    char palavra_digitada [10];
    char letra_digitada;
    int tempo_aleatorio;
    double clock;
    int eq;
    char fator_eq[3];
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
        eq = fator_equilibrio(a, 3);
        calcula_x_arv(a, 0);
        calcula_y_arv(a, 50, 30);
        printa_arv(a);
        to_char(eq, fator_eq);
        if(eq<=1 && eq>=-1){
            tela_texto(800,50,30,8, fator_eq);
        }
        else if(eq<=2 && eq>=-2){
            tela_texto(800,50,30,2, fator_eq);
        }
        else{
            break;
            // TODO: tela de derrota
        }
        tela_texto(100,50,20,8,"proxima palavra:");
        tela_texto(100,50,20,8,"proxima palavra:");
        tela_texto(275,50,20,8,proxima_palavra);
        tela_texto(125,tam_y-50,20,8,"palavra sendo escrita:");
        tela_texto(300,tam_y-50,20,8,palavra_digitada);
        tela_atualiza();
    }
    tela_fim();
    return 0;
}
