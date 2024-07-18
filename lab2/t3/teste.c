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
    jogoIni(10, 2, 3, j);
    tela_menu(j);
    if(j->dificuldade == 0){
        printf("fazer a tela dos recordes\n");
    }
    int teste = tela_jogo(j);
    char* a= "teste";
    salva_recorde(a, teste);
    tela_fim();
    return 0;
}
