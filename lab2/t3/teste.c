#include "arvore.h"
#include "telag.h"
#include "in_game.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    Jogo j = jogoIni(2, 10, 2, 3);
    int teste = tela_jogo(j);
    char* a= "teste";
    salva_recorde(a, teste);
    tela_fim();
    return 0;
}
