#include "arvore.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int r = 1;
    char palavra[15];
    Arv arvore = NULL;
    while(r>0 && r<4){
        printf("Oq fazer?\n1 - Inserir\n2 - Remover\n3 - Printar\noutro - finaliza\n");
        scanf("%d", &r);
        getchar();
        if(r == 1){
            system("clear");
            printf("Insira a palavra:\n");
            if(fgets(palavra, sizeof(palavra), stdin) != NULL){
                arvore = insere_arv(arvore, palavra);
            }
            system("clear");
        }
        else if(r == 2){
            // system("clear");
            printf("Insira a palavra: \n");
            if(fgets(palavra, sizeof(palavra), stdin) != NULL){
                arvore = remove_arv(arvore, palavra);
            }
            system("clear");
        }
        else{
            system("clear");
            // printa_arv(arvore);
            printa_arv(arvore, 0);
        }
    }
    return 0;
}
