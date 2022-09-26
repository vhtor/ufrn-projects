#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_LINE_LENGTH 50

int **matriz_a, **matriz_b, **matriz_c;

void imprimeMatriz(int **matriz, int linhas, int colunas) 
{
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      printf("%d", matriz[i][j]);
      printf(" ");
    }
    printf("\n\n");
  }
}

void leMatriz(FILE *arquivo, int **matriz, int linhas, int colunas) {
  char line[MAX_LINE_LENGTH], ch;
  int count = 0;
  int linha, coluna, valor;
  while (fgets(line, MAX_LINE_LENGTH, arquivo)) {
    if (count > 0) {
      sscanf(line, "%*c %d %d %d", &linha, &coluna, &valor);
      matriz[linha-1][coluna-1] = valor;
    }
    count++;
  }
}

int main(int argc, char *argv[]) 
{
  // Lendo arquivos das matrizes
  FILE *arquivo_matriz_a, *arquivo_matriz_b, *arquivo_matriz_c;

  if ((arquivo_matriz_a = fopen(argv[1], "r")) == NULL) 
  {
    printf("Erro! O arquivo 1 não pôde ser aberto.");
    exit(1);
  }

  if ((arquivo_matriz_b = fopen(argv[2], "r")) == NULL) 
  {
    printf("Erro! O arquivo 2 não pôde ser aberto.");
    exit(1);
  }

  // Lendo as dimensões das matrizes
  int linhas_a, colunas_a, linhas_b, colunas_b;
  fscanf(arquivo_matriz_a, "%d %d", &linhas_a, &colunas_a);
  fscanf(arquivo_matriz_b, "%d %d", &linhas_b, &colunas_b);

  // Alocando as matrizes
  matriz_a = malloc(sizeof(int *) * linhas_a);
  for (int i = 0; i < linhas_a; i++) {
    matriz_a[i] = (int *) malloc(sizeof(int *) * colunas_a);
  }

  matriz_b = malloc(sizeof(int *) * linhas_b);
  for (int i = 0; i < linhas_b; i++) {
    matriz_b[i] = (int *) malloc(sizeof(int *) * colunas_b);
  }

  matriz_c = malloc(sizeof(int *) * linhas_a);
  for (int i = 0; i < linhas_a; i++) {
    matriz_c[i] = (int *) malloc(sizeof(int *) * colunas_b);
  }

  leMatriz(arquivo_matriz_a, matriz_a, linhas_a, colunas_a);
  leMatriz(arquivo_matriz_b, matriz_b, linhas_b, colunas_b);
   

  int aux = 0;
  unsigned long time_diff;
  if (colunas_a == linhas_b) 
  {
    int x;
    // Processamento e saida em tela  =  PRODUTO DAS MATRIZES
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    for (int i = 0; i < linhas_a; i++) 
    {
      for (int j = 0; j < colunas_b; j++) 
      {
        for (x = 0; x < linhas_b; x++) {
          aux += matriz_a[i][x] * matriz_b[x][j];
        }
        matriz_c[i][j] = aux;
        aux = 0;
      }
    }
    gettimeofday(&stop, NULL);
    time_diff = ((stop.tv_sec - start.tv_sec) * 1000) + ((stop.tv_usec - start.tv_usec) / 1000.0);
    printf("Tempo: %lu [ms]\n", time_diff);
    
    if ((arquivo_matriz_c = fopen("matriz_c.txt", "w")) == NULL) 
    {
      printf("Erro! O arquivo 3 não pôde ser aberto.");
      exit(1);
    }

    fprintf(arquivo_matriz_c, "%d %d\n", linhas_a, colunas_b);
    for (int i = 0; i < linhas_a; i++) {
      for (int j = 0; j < colunas_b; j++) 
      {
        fprintf(arquivo_matriz_c, "c%d%d ", i+1, j+1);
        fprintf(arquivo_matriz_c,"%d \n", matriz_c[i][j]);
      }
    }
    fprintf(arquivo_matriz_c, "%lu\n", time_diff);

    // Liberando as memórias das matrizes
    for (int i = 0; i < linhas_a; i++) free(matriz_a[i]);
    free(matriz_a);
    
    for (int i = 0; i < linhas_b; i++) free(matriz_b[i]);
    free(matriz_b);

    for (int i = 0; i < linhas_a; i++) free(matriz_c[i]);
    free(matriz_c);

    // Fechando os arquivos
    fclose(arquivo_matriz_a);
    fclose(arquivo_matriz_b);
  }

  else 
  {
    printf("Digite uma matriz válida para multiplicação: \n");
    printf("O número de colunas da primeira matriz deve ser igual o número de linhas da segunda\n");
    exit(0);
  }

  return 0;
}

// Shell Script para executar varias vezes
// Matriz 3200x3200 leva em média 205567ms para multiplicar
// for run in {1..10}; do ./sequencial matriz_a.txt matriz_b.txt; done