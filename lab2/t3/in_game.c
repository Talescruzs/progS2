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
    j->input_p->tentou_remover = 0;
    if(j->input_p->letra_digitada=='\n'){
        Arv *arv_ant = j->arvore;
        j->arvore = remover_no(j->arvore, j->input_p->palavra_digitada);
        if(!compara_arv(arv_ant, j->arvore)){
            j->pontos = j->pontos+(5*j->dificuldade);
            printf("mudou\n");
            // j->arvore->foi_mudada = 0;
        }
        j->input_p->palavra_digitada[0] = '\0';
        j->input_p->tentou_remover = 1;
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
    j->pontos = 0;

    return j;
}

Jogo jogoIni(int tam, int temp_max, int max_eq, int dificuldade){
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
    j->dificuldade = dificuldade;
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

//  TELAS:
void tela_menu(){

}
int tela_jogo(Jogo j){
    int eq = 0;
    char pontos[10];
    char fator_eq[3];
    int cor;
    while(1){
        verifica_tempo(j->relogio, 10);
        if(j->relogio->palavra_mudou){
            troca_palavra(j);
            j->pontos+=2*j->dificuldade;
        }
        controle_input(j);

        if(j->relogio->palavra_mudou || j->input_p->tentou_remover){
            arruma_altura(j->arvore);
            eq = fator_equilibrio(j->arvore);
            calcula_x_arv(j->arvore, 0);
            calcula_y_arv(j->arvore, 50, 30);
        }

        printa_arv(j->arvore, j->max_equilibrio);
        sprintf(fator_eq, "%d", eq);
        sprintf(pontos, "%d", j->pontos);

        if(eq<j->max_equilibrio && eq>j->max_equilibrio*-1){
            cor = 8;
        }
        else if(eq==j->max_equilibrio || eq==j->max_equilibrio*-1){
            cor = 2;
        }
        else{
            return j->pontos;
            // tela_texto(800,50,30,2, fator_eq);
            // TODO: tela de derrota
        }
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX-50,j->tela_total->iniY,30,cor, "Equilibrio");
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX,j->tela_total->iniY,30,cor, fator_eq);
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX-150,j->tela_total->iniY+30,30,8, "Pontos");
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX,j->tela_total->iniY+30,30,8, pontos);
        tela_texto(100,50,20,8,"proxima palavra:");
        tela_texto(100,50,20,8,"proxima palavra:");
        tela_texto(275,50,20,8,j->prox_p->palavra);
        tela_texto(125,j->tela_total->tamY-j->tela_total->iniY,20,8,"palavra sendo escrita:");
        tela_texto(300,j->tela_total->tamY-j->tela_total->iniY,20,8,j->input_p->palavra_digitada);
        tela_atualiza();
    }
}

void salva_recorde(char* jogador, int recorde){
    FILE *arq;
    arq = fopen("recorde.txt", "a");
    if(arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        fclose(arq);
        exit(1); 
    }
    fprintf(arq, "%s: %d\n", jogador, recorde);

    fclose(arq);

}