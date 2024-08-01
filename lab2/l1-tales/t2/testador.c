#include "fila.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trata(Fila self, char op){
    if(op=='a'){
        int v; 
        char a;
        system("clear");
        printf("a = automatico\n");
        printf("!a = manual\n");
        scanf(" %c", &a);
        if(a=='a'){
            for(int i = 0; i<100; i++){
                v = i*2;
                fila_insere(self, &v);
            }
        } else{
            printf("Insira um valor\n");
            scanf("%d", &v);
            fila_insere(self, &v);
        }
    }
    else if(op=='p'){
        int i=0, v=0;
        char a;
        system("clear");
        // Dep d = depura(self);
        // printf("Dados da fila:\n");
        // printf("capacidade = %d\n", d->cap);
        // printf("inicio = %d\n", d->ini);
        // printf("n_elementos = %d\n", d->n_elem);
        fila_inicia_percurso(self, 0);
        while (fila_proximo(self, &v)) {
            printf("- L %d: %d\n", i, v);
            i++;
        }
        printf("-------\n");
        printf("insira p para seguir\n");
        while(a!='p'){
            scanf("%c", &a);
        }
    }
    else if(op=='d'){
        fila_remove(self, NULL);
    }
}

int main(){
    char a;
    Fila f = fila_cria(sizeof(int));
    while(a!='s'){
        system("clear");
        printf("Operacoes na fila:\n");
        printf("a: append\n");
        printf("d: remove\n");
        printf("p: print\n");
        printf("s: stop\n");
        scanf("%c", &a);
        trata(f, a);
    }
    return 0;
}
