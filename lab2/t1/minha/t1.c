// l224a - trabalho 1 - revisão
//
// Aluno: Tales Cruz da Silva
//
// Você deve alterar este arquivo colocando seu nome na linha acima, e nas linhas 
// delimitadas por comentários indicativos. O restante do arquivo não deve ser
// alterado para implementar a parte I do trabalho.
// Pode adicionar includes também.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// tipo de dados que representa um triângulo
typedef struct {
  float lado1;
  float lado2;
  float lado3;
  int tipo;
} triangulo;

// número máximo de triângulos suportado pelo programa
#define MAX_TRIANGULOS 100

// // tipo de dados que representa um vetor de triângulos
// typedef struct {
//   int n_triangulos;                     // número de triângulos no vetor
//   triangulo triangulos[MAX_TRIANGULOS]; // vetor com os triângulos
// } vetor_de_triangulos;

typedef struct {
    int max_triangulos;    // número máximo de triângulos que cabe no vetor
    int n_triangulos;      // número de triângulos atualmente no vetor
    triangulo *triangulos; // ponteiro para o primeiro triângulo do vetor
} vetor_de_triangulos;


// essa função deve existir e ser usada para a leitura de um triângulo.
// lê os valores dos 3 lados de um triângulo,
//   inicializa o triângulo apontado por t com esses valores.
// retorna true se bem sucedido ou false em caso de problema (que pode acontecer na
//   parte II)
bool le_triangulo(triangulo *t, FILE * file, int *n_triangulos_arquivo, int n_t){
  
  if(*n_triangulos_arquivo == 0){
    fscanf(file, "%d", n_triangulos_arquivo);

    if(*n_triangulos_arquivo>n_t){
      printf("Foram solicitados menos triangulos que o total, mostraremos apenas os pedidos!\n");
    }
    else if(*n_triangulos_arquivo<n_t){
      printf("Foram solicitados mais triangulos que o total, erro!\n");
      return false;
    }
  }
  fscanf(file, "%f", &t->lado1);
  fscanf(file, "%f", &t->lado2);
  fscanf(file, "%f", &t->lado3);

  return true;
}

// Você deve implementar as funções faltantes e outras que achar necessário
// abaixo desta linha

void classifica_triangulos(vetor_de_triangulos *triangulos){
  for(int i=0; i<triangulos->n_triangulos; i++){
    if(triangulos->triangulos[i].lado1+triangulos->triangulos[i].lado2<triangulos->triangulos[i].lado3 || triangulos->triangulos[i].lado1+triangulos->triangulos[i].lado3<triangulos->triangulos[i].lado2 || triangulos->triangulos[i].lado3+triangulos->triangulos[i].lado2<triangulos->triangulos[i].lado1){
      triangulos->triangulos[i].tipo = 0;
    }
    else if(triangulos->triangulos[i].lado1==triangulos->triangulos[i].lado2 && triangulos->triangulos[i].lado1 == triangulos->triangulos[i].lado3){
      triangulos->triangulos[i].tipo = 1;
    }
    else if(triangulos->triangulos[i].lado1==triangulos->triangulos[i].lado2 || triangulos->triangulos[i].lado1==triangulos->triangulos[i].lado3 || triangulos->triangulos[i].lado3==triangulos->triangulos[i].lado2){
      triangulos->triangulos[i].tipo = 2;
    }
    else{
      triangulos->triangulos[i].tipo = 3;
    }
  }
}
void conta_triangulos(vetor_de_triangulos *triangulos, int c[4]){
  for(int i=0; i<triangulos->n_triangulos; i++){
    if(triangulos->triangulos[i].tipo == 1){
      c[1]++;
    }
    else if(triangulos->triangulos[i].tipo == 2){
      c[2]++;
    }
    else if(triangulos->triangulos[i].tipo == 3){
      c[3]++;
    }
    else{
      c[0]++;
    }
  }
}
bool le_triangulos(vetor_de_triangulos *triangulos, FILE * file){
  int n_triangulos_arquivo = 0;
  bool a = true;

  for(int i=0; i<triangulos->max_triangulos && a==true; i++){
    a = le_triangulo(&triangulos->triangulos[i], file, &n_triangulos_arquivo, triangulos->max_triangulos);
    if(a){
      triangulos->n_triangulos++;
    }
  }
  
  fclose(file);
  return a;
}
vetor_de_triangulos *aloca_vetor_de_triangulos(int n_triangulos) {
    vetor_de_triangulos *vetor = malloc(sizeof(vetor_de_triangulos));
    if (vetor == NULL) {
        return NULL;
    }
    vetor->max_triangulos = n_triangulos;
    vetor->n_triangulos = 0;
    vetor->triangulos = malloc(n_triangulos * sizeof(triangulo));
    if (vetor->triangulos == NULL) {
        free(vetor);
        return NULL;
    }
    return vetor;
}

int main()
{
  FILE * file;
  file = fopen("texto.txt", "r");
  if(file==NULL){
    printf("Arquivo de leitura não encontrado :(\n");
  }
  else{
    int n_t;
    int contadores[4] = { 0 };
    bool a = true;

    printf("Número de triângulos: ");
    scanf("%d", &n_t);
    // if (n_t < 1 || n_t > MAX_TRIANGULOS) {
    //   printf("Deve ser entre %d e %d\n", 1, MAX_TRIANGULOS);
    //   return 5;
    // }
    // vetor.n_triangulos = n_t;

    vetor_de_triangulos *vetor = aloca_vetor_de_triangulos(n_t);
    if(vetor == NULL){
      printf("Não foi possivel alocar este numero de trinangulos, desculpe :(\n");
    }
    else{
      a = le_triangulos(vetor, file);
      if(a){
        classifica_triangulos(vetor);  
        conta_triangulos(vetor, contadores);
        printf("Classificação dos triângulos:\n");
        printf("  %d equiláteros\n", contadores[1]);
        printf("  %d isósceles\n", contadores[2]);
        printf("  %d escalenos\n", contadores[3]);
        printf("  %d não triângulos\n", contadores[0]);
      }
    }
  }
  return 0;
}
