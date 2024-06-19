#include "arvore.h"
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
    int i = 0;
    int tempo_aleatorio;
    while(i<100){
        cria_palavra(proxima_palavra);
        printf("proxima palavra :%s\n\n", proxima_palavra);
        printa_arv(a, 0);
        tempo_aleatorio = rand()%5;
        waitFor(tempo_aleatorio);
        system("clear");
        a = insere(a, proxima_palavra);
        i++;
    }
    return 0;
}
