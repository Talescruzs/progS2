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
Botao cria_bt(){
    Botao b = (Botao)malloc(sizeof(struct botao));
    assert(b != NULL);
    b->esp = cria_espaco();
    return b;
}
Recorde cria_recorde(){
    Recorde r = (Recorde)malloc(sizeof(struct recorde));
    assert(r != NULL);
    r->esp = cria_espaco();
    r->prox = NULL;
    return r;
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
void seta_bt(Jogo j, int tamX, int tamY, int iniX, int iniY, int retorno, char *palavra){
    if(j->bts==NULL){
        j->bts = cria_bt();
        j->bts->esp->iniX = iniX;
        j->bts->esp->iniY = iniY;
        j->bts->esp->tamY = tamY;
        j->bts->esp->tamX = tamX;
        j->bts->retorno = retorno;
        j->bts->prox = NULL;
        strcpy(j->bts->palavra, palavra);
    }
    else{
        Botao temp = j->bts;
        while(temp->prox != NULL){
            temp=temp->prox;
        }
        Botao prox = cria_bt();
        prox->esp->iniX = iniX;
        prox->esp->iniY = iniY;
        prox->esp->tamX = tamX;
        prox->esp->tamY = tamY;
        prox->retorno = retorno;
        prox->prox = NULL;
        strcpy(prox->palavra, palavra);
        temp->prox = prox;
    }
    
}
void le_recorde(Jogo j){
    FILE *arq;
    arq = fopen("recorde.txt", "r");
    if(arq == NULL){
        printf("Erro, nao foi possivel abrir o arquivo\n");
        fclose(arq);
        exit(1); 
    }
    char nome[10];
    int pontos;
    char dificuldade[100];
    int count = 0;
    
    Recorde temp = j->recorde;
    while (fscanf(arq, "%s %d %s", nome, &pontos, dificuldade) == 3) {
        temp->pts = pontos;
        strcpy(temp->usuario, nome);
        strcpy(temp->dificuldade, dificuldade);
        if(count == 0){
            temp->esp->iniX = j->tela_total->iniX+(j->tela_total->tamX/5)*2;
            temp->esp->iniY = 50+(j->tela_total->tamY/5)*1;
            temp->esp->tamX = j->tela_total->tamX/4;
            temp->esp->tamY = j->tela_total->tamY/7;
        }
        else if(count == 1){
            temp->esp->iniX = j->tela_total->iniX+(j->tela_total->tamX/5)*1;
            temp->esp->iniY = 50+(j->tela_total->tamY/5)*2;
            temp->esp->tamX = j->tela_total->tamX/4;
            temp->esp->tamY = j->tela_total->tamY/7;
        }
        if(count == 2){
            temp->esp->iniX = j->tela_total->iniX+(j->tela_total->tamX/5)*3;
            temp->esp->iniY = 50+(j->tela_total->tamY/5)*2;
            temp->esp->tamX = j->tela_total->tamX/4;
            temp->esp->tamY = j->tela_total->tamY/7;
            temp->prox = NULL;
            break;
        }
        temp->prox=cria_recorde();
        temp = temp->prox;
        count++;
    }
    fclose(arq);
}
void destroi_bts(Jogo j){
    if(j->bts==NULL) return;

    while(j->bts != NULL){
        Botao temp = j->bts;
        j->bts=j->bts->prox;
        free(temp->esp);
        free(temp);
    }
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
void verifica_tempo(Relogio relogio, int tempo_max, int tempo_min){
    if(tela_relogio()>=relogio->clock_utlima_mudanca+relogio->tempo_aleatorio){
        relogio->clock_utlima_mudanca = tela_relogio();
        while(relogio->tempo_aleatorio<tempo_min){
            relogio->tempo_aleatorio = rand()%tempo_max;
        }
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
    j->prox_p = cria_palavra_str();
    j->input_p = cria_input_p();
    j->relogio = cria_relogio();
    j->pontos = 0;

    return j;
}

void jogoIni(int temp_max, int max_eq, int dificuldade, Jogo j){
    ini_relogio(j->relogio, temp_max);
    j->arvore = cria_arv();

    j->max_equilibrio = max_eq;
    j->dificuldade = dificuldade;
}
void jogoFim(){
    ;
}
void remove_ultima_letra(char *p){
    for(int i=0; p[i]!='\0'; i++){
        if(p[i+1] == '\0'){
            p[i] = '\0';
        }
    }
}
void seta_ultima_letra(char *p, char l, int tam){
    for(int i=0; i<tam; i++){
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
Jogo ini_tela(){
    int tam = 0;
    while(tam<=0||tam>3){
        printf("TAMANHOS DE TELA:\n1- pequena(1000X500)\n2- media(1400X700)\n3- grande(1800X900)\nInsira o tamanho desejado:\n");
        scanf("%d", &tam);
    }
    Jogo j = cria_jogo();
    if(tam == 1){
        seta_tela(j->tela_total, 1000, 500, 5, 10);
        j->tam_letra = 20;
    }
    else if(tam == 2){
        seta_tela(j->tela_total, 1400, 700, 5, 10);
        j->tam_letra = 25;
    }
    else if(tam == 3){
        seta_tela(j->tela_total, 1800, 900, 5, 10);
        j->tam_letra = 30;
    }
    else{
        exit(1);
    }
    tela_inicio(j->tela_total->tamX+(2*j->tela_total->iniX), j->tela_total->tamY+(2*j->tela_total->iniY), "joguinho super legal");
    ini_palavra(j->prox_p, j->tam_letra);
    return j;
}
void tela_menu(Jogo j){
    int corbt=8;
    int corus=8;
    int posX = 0;
    int posY = 0;
    seta_bt(j, j->tela_total->tamX/5, j->tela_total->tamY/7, j->tela_total->iniX+(j->tela_total->tamX/5)*0.5, j->tela_total->tamY-(j->tela_total->tamY/7)*4, 3, "FACIL");
    seta_bt(j, j->tela_total->tamX/5, j->tela_total->tamY/7, j->tela_total->iniX+(j->tela_total->tamX/5)*2, j->tela_total->tamY-(j->tela_total->tamY/7)*4, 2, "MEDIO");
    seta_bt(j, j->tela_total->tamX/5, j->tela_total->tamY/7, j->tela_total->iniX+(j->tela_total->tamX/5)*3.5, j->tela_total->tamY-(j->tela_total->tamY/7)*4, 1, "DIFICIL");
    seta_bt(j, j->tela_total->tamX/5, j->tela_total->tamY/7, j->tela_total->iniX+(j->tela_total->tamX/5)*2, j->tela_total->tamY-(j->tela_total->tamY/7)*2, 0, "RECORDES");
    seta_bt(j, j->tela_total->tamX/10, j->tela_total->tamY/10, j->tela_total->iniX+(j->tela_total->tamX/5)*4, j->tela_total->tamY-(j->tela_total->tamY/7)*1, -1, "FECHAR");
    while(1){
        controle_input(j);
        tela_texto_dir((j->tela_total->tamX/2)-j->tam_letra*7,j->tela_total->iniY,j->tam_letra,corus,"USUARIO:");
        corus = 8;
        tela_texto_dir((j->tela_total->tamX/2),j->tela_total->iniY,j->tam_letra,8,j->input_p->palavra_digitada);
        Botao temp = j->bts;
        tela_rato_pos(&posX, &posY);
        tela_circulo(posX, posY, 2*j->tam_letra/10, 0, 8, 8);
        while(temp!=NULL){
            if(posX>=temp->esp->iniX&&posX<=temp->esp->iniX+temp->esp->tamX&&posY>=temp->esp->iniY&&posY<=temp->esp->iniY+temp->esp->tamY){
                corbt = 2;
                if(tela_rato_clicado()){
                    if(j->input_p->palavra_digitada[0]=='\0'&&(temp->retorno!=0&&temp->retorno!=-1)){
                        corus = 2;
                    }
                    else{
                        strcpy(j->jogador, j->input_p->palavra_digitada);
                        j->input_p->palavra_digitada[0] = '\0';
                        if(temp->retorno == 3){
                            jogoIni(10, 3, 3, j);
                        }
                        else if(temp->retorno == 2){
                            jogoIni(6, 2, 2, j);
                        }
                        else if(temp->retorno == 1){
                            jogoIni(4, 1, 1, j);
                        }
                        else{
                            j->dificuldade = temp->retorno;
                        }
                        destroi_bts(j);
                        return;
                    }
                }
            }
            tela_retangulo(temp->esp->iniX, temp->esp->iniY, temp->esp->iniX+temp->esp->tamX, temp->esp->iniY+temp->esp->tamY, 2, corbt, 0);
            tela_texto(temp->esp->iniX+(temp->esp->tamX/2),temp->esp->iniY+(temp->esp->tamY/2),j->tam_letra,corbt,temp->palavra);
            temp = temp->prox;
            corbt = 8;
        }
        tela_atualiza();
    }
}
void tela_jogo(Jogo j){
    int eq = 0;
    char pontos[10];
    char fator_eq[3];
    int cor;
    char tempo[10];
    while(1){
        verifica_tempo(j->relogio, 3*j->dificuldade, j->dificuldade);
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
            return;
        }
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX-50,j->tela_total->iniY,j->tam_letra,cor, "Equilibrio");
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX,j->tela_total->iniY,j->tam_letra,cor, fator_eq);
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX-150,j->tela_total->iniY+30,j->tam_letra,8, "Pontos");
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX,j->tela_total->iniY+30,j->tam_letra,8, pontos);
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX-200,j->tela_total->iniY+60,j->tam_letra,8, "Jogador");
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX,j->tela_total->iniY+60,j->tam_letra,8, j->jogador);

        sprintf(tempo, "%lf", j->relogio->tempo_aleatorio-(tela_relogio()-j->relogio->clock_utlima_mudanca));
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX-200,j->tela_total->tamY-j->tela_total->iniY-10,j->tam_letra,8, "Tempo");
        tela_texto_esq(j->tela_total->tamX-j->tela_total->iniX,j->tela_total->tamY-j->tela_total->iniY-10,j->tam_letra,8, tempo);
        tela_texto_dir(10,50,j->tam_letra,8,"proxima palavra:");
        tela_texto_dir(j->tam_letra*10,50,j->tam_letra,8,j->prox_p->palavra);
        tela_texto_dir(10,j->tela_total->tamY-j->tela_total->iniY-10,j->tam_letra,8,"palavra sendo escrita:");
        tela_texto_dir(j->tam_letra*12,j->tela_total->tamY-j->tela_total->iniY-10,j->tam_letra,8,j->input_p->palavra_digitada);
        tela_atualiza();
    }
}
void tela_recordes(Jogo j){
    int corbt=8;
    int posX = 0;
    int posY = 0;
    int count = 1;
    char pontos[10];
    char ranking[2];
    seta_bt(j, j->tela_total->tamX/4, j->tela_total->tamY/7, j->tela_total->iniX+(j->tela_total->tamX/5)*2, j->tela_total->tamY-(j->tela_total->tamY/7)*2, 0, "VOLTAR");
    j->recorde = cria_recorde();
    le_recorde(j);
    while(1){
        Recorde tempr = j->recorde;
        tela_rato_pos(&posX, &posY);
        tela_circulo(posX, posY, 2*j->tam_letra/10, 0, 8, 8);
        tela_texto(j->tela_total->tamX/2, j->tela_total->iniY+50,j->tam_letra,8,"Hall da fama");
        while(tempr!=NULL){
            if(posX>=tempr->esp->iniX&&posX<=tempr->esp->iniX+tempr->esp->tamX&&posY>=tempr->esp->iniY&&posY<=tempr->esp->iniY+tempr->esp->tamY){
                corbt = 3;
            }
            tela_retangulo(tempr->esp->iniX, tempr->esp->iniY, tempr->esp->iniX+tempr->esp->tamX, tempr->esp->iniY+tempr->esp->tamY, 2, corbt, 0);
            sprintf(ranking, "%d", count);
            strcat(ranking, ":");
            tela_texto_dir(tempr->esp->iniX-j->tam_letra*2, tempr->esp->iniY+(tempr->esp->tamY/2.5),j->tam_letra,corbt,ranking);
            sprintf(pontos, "%d", tempr->pts);
            strcat(pontos, "p");
            tela_texto_dir(tempr->esp->iniX+5, tempr->esp->iniY+(tempr->esp->tamY/2.5),j->tam_letra,corbt,pontos);
            tela_texto(tempr->esp->iniX+tempr->esp->tamX/2, tempr->esp->iniY+(tempr->esp->tamY/2.5),j->tam_letra,corbt,tempr->usuario);
            tela_texto_esq(tempr->esp->iniX+tempr->esp->tamX-5, tempr->esp->iniY+(tempr->esp->tamY/2.5),j->tam_letra,corbt,tempr->dificuldade);
            tempr = tempr->prox;
            corbt = 8;
            count++;
        }
        count = 1;
        Botao  tempbt = j->bts;
        while(tempbt!=NULL){
            if(posX>=tempbt->esp->iniX&&posX<=tempbt->esp->iniX+tempbt->esp->tamX&&posY>=tempbt->esp->iniY&&posY<=tempbt->esp->iniY+tempbt->esp->tamY){
                corbt = 2;
                if(tela_rato_clicado()){
                    destroi_bts(j);
                    return;
                }
            }
            tela_retangulo(tempbt->esp->iniX, tempbt->esp->iniY, tempbt->esp->iniX+tempbt->esp->tamX, tempbt->esp->iniY+tempbt->esp->tamY, 2, corbt, 0);
            tela_texto(tempbt->esp->iniX+(tempbt->esp->tamX/2),tempbt->esp->iniY+(tempbt->esp->tamY/2),j->tam_letra,corbt,tempbt->palavra);
            tempbt = tempbt->prox;
            corbt = 8;
        }
        tela_atualiza();
    }
}
void salva_recorde(char *jogador, int recorde, int dificuldade) {
    FILE *arq;
    FILE *arqesc;
    Recorde r = cria_recorde();
    Recorde temp = r;
    char nome[10];
    int pontos = 0;
    char dificuldades[100];
    int count = 0;

    arq = fopen("recorde.txt", "r");
    if (arq == NULL) {
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);
    }

    // Ler o arquivo e criar a lista ligada de recordes
    while (fscanf(arq, "%s %d %s", nome, &pontos, dificuldades) == 3) {
        temp->prox = cria_recorde();
        temp = temp->prox;
        temp->pts = pontos;
        strcpy(temp->usuario, nome);
        strcpy(temp->dificuldade, dificuldades);
        count++;
    }
    fclose(arq);

    // Se o arquivo estava vazio, salva diretamente o novo recorde
    if (count == 0) {
        r->pts = recorde;
        strcpy(r->usuario, jogador);
        if (dificuldade == 3) strcpy(r->dificuldade, "facil");
        else if (dificuldade == 2) strcpy(r->dificuldade, "medio");
        else if (dificuldade == 1) strcpy(r->dificuldade, "dificil");

        arqesc = fopen("recorde.txt", "w");
        if (arqesc == NULL) {
            printf("Erro, nao foi possivel abrir o arquivo\n");
            exit(1);
        }
        fprintf(arqesc, "%s %d %s\n", r->usuario, r->pts, r->dificuldade);
        free(r);
        fclose(arqesc);
        return;
    }

    // Remove o nó inicial vazio
    temp = r->prox;
    free(r);
    r = temp;

    // Criar o novo recorde
    Recorde novo = cria_recorde();
    novo->pts = recorde;
    strcpy(novo->usuario, jogador);
    if (dificuldade == 3) strcpy(novo->dificuldade, "facil");
    else if (dificuldade == 2) strcpy(novo->dificuldade, "medio");
    else if (dificuldade == 1) strcpy(novo->dificuldade, "dificil");

    // Inserir o novo recorde na posição correta
    Recorde prev = NULL;
    temp = r;
    while (temp != NULL && recorde <= temp->pts) {
        prev = temp;
        temp = temp->prox;
    }

    if (prev == NULL) {
        novo->prox = r;
        r = novo;
    } else {
        prev->prox = novo;
        novo->prox = temp;
    }

    // Escrever a lista atualizada no arquivo
    arqesc = fopen("recorde.txt", "w");
    if (arqesc == NULL) {
        printf("Erro, nao foi possivel abrir o arquivo\n");
        exit(1);
    }
    temp = r;
    while (temp != NULL) {
        fprintf(arqesc, "%s %d %s\n", temp->usuario, temp->pts, temp->dificuldade);
        Recorde aux = temp;
        temp = temp->prox;
        free(aux);
    }
    fclose(arqesc);
}
