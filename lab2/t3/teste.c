#include "arvore.h"
#include "tecla.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

int main(){
    Arv *a = cria_arv();
    char proxima_palavra [10];
    char palavra_digitada [10];
    char letra_digitada;
    int i = 0;
    int tempo_aleatorio;
    int clock;
    tecla_ini();
    while(i<100){
        cria_palavra(proxima_palavra);
        printf("proxima palavra :%s\n\n", proxima_palavra);
        printa_arv(a, 0);
        tempo_aleatorio = rand()%5;
        clock = time(0);
        while(time(0) < clock+tempo_aleatorio){
            letra_digitada = tecla_le_char();
            if(letra_digitada=='\n'){
                a = remover_no(a, palavra_digitada);
                palavra_digitada = '\0';
            }
            else{
                strcat(palavra_digitada, &letra_digitada);
                printf("%s\n", palavra_digitada);
            }
        }
        // waitFor(tempo_aleatorio);
        system("clear");
        a = insere(a, proxima_palavra);
        i++;
    }
    tecla_fim();
    return 0;
}
