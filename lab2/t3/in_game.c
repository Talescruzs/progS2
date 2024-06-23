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
Palavra cria_palavra_str(){
    Palavra p = (Palavra)malloc(sizeof(struct palavra));
    assert(p != NULL);
    return p;
}
Input_p cria_input_p(){
    Input_p p = (Input_p)malloc(sizeof(struct input_p));
    assert(p != NULL);
    return p;
}
Relogio cria_relogio(){
    Relogio r = (Relogio)malloc(sizeof(struct relogio));
    assert(r != NULL);
    return r;
}
void seta_tela(Espaco tela, int tamX, int tamY, int bordaX, int bordaY){
    tela->iniX = bordaX;
    tela->iniY = bordaY;
    tela->tamX = tamX-bordaX;
    tela->tamY = tamY-bordaY;
}
void ini_relogio(Relogio relogio, int tempo_max){
    relogio->clock_total = tela_relogio();
    relogio->clock_utlima_mudanca = tela_relogio();
    relogio->tempo_aleatorio = rand()%tempo_max;
}
void ini_palavra(Palavra p, int tam_letra){
    cria_palavra(p->palavra);
    p->tamanho_letra = tam_letra;
}
void troca_palavra(Jogo j){
    j->arvore = insere(j->arvore, j->prox_p->palavra);
    cria_palavra(j->prox_p->palavra);
}
void verifica_tempo(Relogio relogio, int tempo_max){
    if(tela_relogio()>=relogio->clock_utlima_mudanca+relogio->tempo_aleatorio){
        relogio->clock_utlima_mudanca = tela_relogio();
        relogio->tempo_aleatorio = rand()%tempo_max;
        relogio->palavra_mudou = 1;
    }
    else{
        relogio->palavra_mudou = 0;
    }
}
void controle_input(Jogo j){
    j->input_p->letra_digitada = tela_tecla();
    if(j->input_p->letra_digitada=='\n'){
        j->arvore = remover_no(j->arvore, j->input_p->palavra_digitada);
        j->input_p->palavra_digitada[0] = '\0';
    }
    else if(j->input_p->letra_digitada=='\b'){
        remove_ultima_letra(j->input_p->palavra_digitada);
    }
    else if(j->input_p->letra_digitada!=0){
        seta_ultima_letra(j->input_p->palavra_digitada, j->input_p->letra_digitada, 9);
    }
}
int controle_palavra(double ini_temp, int demora){
    double temp_atual = tela_relogio();
    if(temp_atual >= (ini_temp)+demora){
        return 1;
    }
    return 0;
}
Jogo cria_jogo(){
    Jogo j = (Jogo)malloc(sizeof(struct jogo));
    assert(j != NULL);
    j->tela_total = cria_espaco();
    j->header = cria_espaco();
    j->footer = cria_espaco();
    j->prox_p = cria_palavra_str();
    j->input_p = cria_input_p();
    j->relogio = cria_relogio();

    return j;
}

Jogo jogoIni(int tam, int temp_max, int max_eq){
    Jogo j = cria_jogo();
    int tam_letra;
    if(tam == 0){
        seta_tela(j->tela_total, 1000, 500, 5, 10);
        seta_tela(j->header, 150, 500, 0, 0);
        seta_tela(j->footer, 150, 500, 0, 0);
        tam_letra = 30;
    }
    else if(tam == 1){
        seta_tela(j->tela_total, 1400, 700, 5, 10);
        tam_letra = 25;
    }
    else if(tam == 2){
        seta_tela(j->tela_total, 1800, 900, 5, 10);
        tam_letra = 20;
    }
    else{
        exit(1);
    }
    tela_inicio(j->tela_total->tamX+(2*j->tela_total->iniX), j->tela_total->tamY+(2*j->tela_total->iniY), "joguinho super legal");
    ini_palavra(j->prox_p, tam_letra);
    ini_relogio(j->relogio, temp_max);
    j->arvore = cria_arv();

    j->max_equilibrio = max_eq;
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