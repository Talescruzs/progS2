#include "arvore.h"
#include "telag.h"
#include "in_game.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    srand(time(NULL));
    Jogo j = ini_tela();
    j->dificuldade=0;
    while(j->dificuldade!=-1){
        tela_menu(j);
        tela_atualiza();
        if(j->dificuldade > 0){
            tela_jogo(j);
            salva_recorde(j->jogador, j->pontos, j->dificuldade);
            tela_atualiza();
        }
        else if(j->dificuldade == 0){
            tela_recordes(j);
            tela_atualiza();
        }
        j->pontos = 0;
        j->jogador[0] = '\0';
    }
    tela_fim();
    return 0;
}
