#include "in_game.h"
#include "telag.h"
#include "arvore.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Espaco cria_espaco(){
    Espaco e = (Espaco)malloc(sizeof(struct espaco));
    assert(e != NULL);
    return e;
}
Jogo cria_jogo(){
    Jogo j = (Jogo)malloc(sizeof(struct jogo));
    assert(j != NULL);
    j->tela_total = cria_espaco();
    j->header = cria_espaco();
    j->footer = cria_espaco();

    return j;
}
void seta_tela(Espaco tela, int tamX, int tamY, int bordaX, int bordaY){
    tela->iniX = bordaX;
    tela->iniY = bordaY;
    tela->tamX = tamX-bordaX;
    tela->tamY = tamY-bordaY;
}
Jogo jogoIni(int tam){
    Jogo j = cria_jogo();
    if(tam == 0){
        seta_tela(j->tela_total, 1000, 500, 5, 10);
        seta_tela(j->header, 150, 500, 0, 0);
        seta_tela(j->footer, 150, 500, 0, 0);
    }
    else if(tam == 1){
        seta_tela(j->tela_total, 1400, 700, 5, 10);
    }
    else if(tam == 2){
        seta_tela(j->tela_total, 1800, 900, 5, 10);
    }
    else{
        exit(1);
    }

    tela_inicio(j->tela_total->tamX+(2*j->tela_total->iniX), j->tela_total->tamY+(2*j->tela_total->iniY), "joguinho super legal");
    return j;
}
void jogoFim(){
    ;
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
void to_char(int n, char *palavra){
    char modulo;
    if(n>=0){
        modulo = n+'0';
        palavra[0] = '+';
    }
    else if(n<0){
        modulo = (n*-1)+'0';
        palavra[0] = '-';
    }
    palavra[1] = modulo;
    palavra[2] = '\0';
}
void cria_palavra(char *palavra){
    int tamanho_palavras = 3;
    int qtd_total_silabas = 107; 
    int i = 0;
    palavra[0] = '\0';
    char temp[3];
    int indices_aleatorios[tamanho_palavras];
    for(i = 0; i<tamanho_palavras; i++){
        int parte = qtd_total_silabas/tamanho_palavras;
        indices_aleatorios[i] = (rand()%parte)+parte*i;
    }
    FILE *arq;
    arq = fopen("silabas.txt", "r");
    if(arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        fclose(arq);
        exit(1); 
    }
    i = 0;
    int count = 0;
    while(count<=indices_aleatorios[i] && i<tamanho_palavras){
        fscanf(arq, "%s ", temp);
        if(count==indices_aleatorios[i]){
            strcat(palavra, temp);
            i++;
        }
        count++;
    }
    fclose(arq);
}    
void atualiza_game();