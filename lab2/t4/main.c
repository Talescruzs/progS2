#include "grafo.h"

int main(){
    Grafo g = grafo_cria(sizeof(int), sizeof(float));
    
    
    grafo_destroi(g);
    return 0;
}