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
int main(){
    Arv *a = cria_arv();
    char proxima_palavra [10];
    char palavra_digitada [10];
    char letra_digitada;
    int i = 0;
    int tempo_aleatorio;
    int clock;
    tela_inicio(1080, 780, "ababa");
    while(i<10){
        cria_palavra(proxima_palavra);
        tempo_aleatorio = rand()%5;
        // tempo_aleatorio = 0;
        clock = time(0);
        // while(time(0) < clock+tempo_aleatorio){
            // printf("proxima palavra :%s\n\n", proxima_palavra);
            // printa_arv(a, 0);
        // }
        // waitFor(tempo_aleatorio);
        system("clear");
        a = insere(a, proxima_palavra);
        i++;
    }
    printa_arv(a, 0);

    while(1){
        letra_digitada = tela_tecla();
        if(letra_digitada=='\n'){
            a = remover_no(a, palavra_digitada);
            // system("clear");
            printa_arv(a, 0);
            palavra_digitada[0] = '\0';
        }
        else if(letra_digitada=='\b'){
            remove_ultima_letra(palavra_digitada);
            printf("%s", palavra_digitada);
        }
        else if(letra_digitada!=0){
            seta_ultima_letra(palavra_digitada, letra_digitada, 10);
            printf("%s", palavra_digitada);
        }
        tela_texto(400,400,30,8,palavra_digitada);
        tela_atualiza();
    }
    tela_fim();
    return 0;
}
