#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_LINE_LENGTH 50

int **matriz_a, **matriz_b, **matriz_c;
int linhas_a, colunas_a, linhas_b, colunas_b;
int P;
double fileCtrl;

FILE *arquivo_linha_matriz_c;

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

void* multMatrix(void* x) 
{
  int iterator = (int)(size_t)x;
  //printf("------------------ Thread [%d] começou ------------------\n", iterator);
  int acc = 0;
  int linha_matriz_c[colunas_b];
  
  unsigned long time_diff;
  struct timeval stop, start;
  gettimeofday(&start, NULL);

  for (int i = 0; i < linhas_a; i++) {
    for (int j = 0; j < colunas_b; j++) {
      acc += matriz_a[iterator][j] * matriz_b[j][i];
    }
    linha_matriz_c[i] = acc;
    acc = 0;
  }

  for (int n = 0; n < colunas_b; n++) {
    fprintf(arquivo_linha_matriz_c, "c%d%d %d\n", iterator+1, n+1, linha_matriz_c[n]);
  }
  
  gettimeofday(&stop, NULL);
  time_diff = ((stop.tv_sec - start.tv_sec) * 1000) + ((stop.tv_usec - start.tv_usec) / 1000.0);
  fprintf(arquivo_linha_matriz_c, "%lu\n", time_diff);
  //printf("------------------ Thread [%d] terminou ------------------\n", iterator);
  pthread_exit(NULL);
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
  fscanf(arquivo_matriz_a, "%d %d", &linhas_a, &colunas_a);
  fscanf(arquivo_matriz_b, "%d %d", &linhas_b, &colunas_b);

  // Alocando as matrizes
  matriz_a = malloc(sizeof(int *) * linhas_a);
  for (int i = 0; i < linhas_a; i++) {
    matriz_a[i] = (int*) malloc(sizeof(int) * colunas_a);
  }

  matriz_b = malloc(sizeof(int *) * linhas_b);
  for (int i = 0; i < linhas_b; i++) {
    matriz_b[i] = (int*) malloc(sizeof(int) * colunas_b);
  }

  matriz_c = malloc(sizeof(int *) * linhas_a);
  for (int i = 0; i < linhas_a; i++) {
    matriz_c[i] = (int*) malloc(sizeof(int) * colunas_b);
  }

  leMatriz(arquivo_matriz_a, matriz_a, linhas_a, colunas_a);
  leMatriz(arquivo_matriz_b, matriz_b, linhas_b, colunas_b);
  fclose(arquivo_matriz_a);
  fclose(arquivo_matriz_b);

  P = atoi(argv[3]);
  pthread_t tid[P];

  if (colunas_a == linhas_b) 
  {
    struct timeval fim, inicio;
    gettimeofday(&inicio, NULL);
    for (int j = 0; j < P; j++) 
    {
      char filename[25];
      sprintf(filename, "output/linha_%d_matriz_c", j+1);

      if ((arquivo_linha_matriz_c = fopen(filename, "w")) == NULL) {
        printf("Erro! O arquivo 1 não pôde ser aberto.");
        exit(1);
      }

      fprintf(arquivo_linha_matriz_c, "%d %d\n", linhas_a, colunas_b);
      pthread_create(&tid[j], NULL, multMatrix, (void *)(size_t)j);
    }

    for (int j = 0; j < P; j++) {
      pthread_join(tid[j], NULL);
    }

    gettimeofday(&fim, NULL);
    unsigned long time_diff = ((fim.tv_sec - inicio.tv_sec) * 1000) + ((fim.tv_usec - inicio.tv_usec) / 1000.0);
    printf("Tempo: %lu [ms]\n", time_diff);

    // Liberando as memórias das matrizes
    for (int i = 0; i < linhas_a; i++) free(matriz_a[i]);
    free(matriz_a);
    
    for (int i = 0; i < linhas_b; i++) free(matriz_b[i]);
    free(matriz_b);

    for (int i = 0; i < linhas_a; i++) free(matriz_c[i]);
    free(matriz_c);
    
    fclose(arquivo_linha_matriz_c);
  }
  
  else 
  {
    printf("Digite uma matriz válida para multiplicação: \n");
    printf("O número de colunas da primeira matriz deve ser igual o número de linhas da segunda\n");
    exit(0);
  } 
  
  return 0;
}

// Scripts

// Remover todos os arquivos de linhas gerados: rm output/*
// Gerar matrizes ./auxiliar m n m n
// Executar o programa de threads ./threads matriz_a.txt matriz_b.txt P
// for run in {1..10}; do ./threads matriz_a.txt matriz_b.txt P; done