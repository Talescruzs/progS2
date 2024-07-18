#include "arvore.h"
#include "telag.h"
#include "in_game.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    Jogo j = ini_tela();
    j->dificuldade=0;
    tela_menu(j);
    if(j->dificuldade == 0){
        printf("fazer a tela dos recordes\n");
    }
    else{
        tela_jogo(j);
        salva_recorde(j->jogador, j->pontos, j->dificuldade);
    }
    tela_fim();
    return 0;
}
