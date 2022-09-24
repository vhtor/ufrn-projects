#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

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

int main(int argc, char *argv[]) 
{
  // Definição de variaveis
  // Matriz A
  int **matriz_A;
  int linhas_A = atoi(argv[1]);
  int colunas_A = atoi(argv[2]);
  matriz_A = malloc(sizeof(int *) * linhas_A);
  for (int i = 0; i < linhas_A; i++) {
    matriz_A[i] = malloc(sizeof(int *) * colunas_A);
  }

  // Matriz B
  int **matriz_B;
  int linhas_B = atoi(argv[3]);
  int colunas_B = atoi(argv[4]);
  matriz_B = malloc(sizeof(int *) * linhas_B);
  for (int i = 0; i < linhas_B; i++) {
    matriz_B[i] = malloc(sizeof(int *) * colunas_B);
  }

  // Preenchimento aleatório de matrizes
  for (int i = 0; i < linhas_A; i++)
  {
    for (int j = 0; j < colunas_A; j++) 
    {
      matriz_A[i][j] = rand() % 10;
      //printf(" ");
    }
    //printf(" \n");
  }

  for (int i = 0; i < linhas_B; i++) 
  {
    for (int j = 0; j < colunas_B; j++) 
    {
      matriz_B[i][j] = rand() % 10;
      //printf(" ");
    }
    //printf(" \n ");
  }
  
  int matriz_C[linhas_A][colunas_B], aux = 0;

  // Imprime as matrizes definidas
  /* printf("---------------------------- 1ª Matriz Gerada ---------------------------------\n\n");
  imprimeMatriz(matriz_A, linhas_A, colunas_A);
  printf("---------------------------- 2ª Matriz Gerada ---------------------------------\n\n");
  imprimeMatriz(matriz_B, linhas_B, colunas_B); */
 
  if (colunas_A == linhas_B) 
  {
    int x;
    // Processamento e saida em tela  =  PRODUTO DAS MATRIZES
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    for (int i = 0; i < linhas_A; i++) 
    {
      for (int j = 0; j < colunas_B; j++) 
      {
        matriz_C[i][j] = 0;
        for (x = 0; x < linhas_B; x++) {
          aux += matriz_A[i][x] * matriz_B[x][j];
        }
        matriz_C[i][j] = aux;
        aux = 0;
      }
    }
    gettimeofday(&stop, NULL);
    unsigned long time_diff = ((stop.tv_sec - start.tv_sec) * 1000) + ((stop.tv_usec - start.tv_usec) / 1000.0);
    printf("\nTempo: %lu [ms]\n", time_diff);
  }

  else 
  {
    printf("Digite uma matriz válida para multiplicação: \n");
    printf("O número de colunas da primeira matriz deve ser igual o número de linhas da segunda\n");
    exit(0);
  }

  // Liberando as memórias das matrizes
  for (int i = 0; i < linhas_A; i++) free(matriz_A[i]);
  free(matriz_A);
  
  for (int i = 0; i < linhas_B; i++) free(matriz_B[i]);
  free(matriz_B);
  
  return 0;
}

// Shell Script para executar varias vezes
// for run in {1..10}; do ./sequencial 100 100 100 100; done
// for run in {1..10}; do ./sequencial 200 200 200 200; done
// for run in {1..10}; do ./sequencial 300 300 300 300; done
// for run in {1..10}; do ./sequencial 400 400 400 400; done
// for run in {1..10}; do ./sequencial 500 500 500 500; done