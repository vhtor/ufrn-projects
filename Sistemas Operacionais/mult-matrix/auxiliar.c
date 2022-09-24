#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char const *argv[])
{
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
  for (int i = 0; i < linhas_A; i++) {
    for (int j = 0; j < colunas_A; j++) {
      matriz_A[i][j] = rand() % 10;
    }
  }

  for (int i = 0; i < linhas_B; i++) {
    for (int j = 0; j < colunas_B; j++) {
      matriz_B[i][j] = rand() % 10;
      printf(" ");
    }
    printf(" \n ");
  }

  FILE *arquivo_matriz;
  arquivo_matriz = fopen("matrizes.txt", "w");

  // Escrevendo as linhas e colunas da matriz
  fprintf(arquivo_matriz, "%d %d\n", linhas_A, colunas_A);

  // Escrevendo os valores da matriz
  for (int i = 0; i < linhas_A; i++) {
    for (int j = 0; j < colunas_A; j++) {
      fprintf(arquivo_matriz, "a%d%d ", i+1, j+1);
      fprintf(arquivo_matriz,"%d \n", matriz_A[i][j]);
    }
  }
  fprintf(arquivo_matriz, "\n");

  fprintf(arquivo_matriz, "%d %d\n", linhas_B, colunas_B);
  // Escrevendo os valores da matriz
  for (int i = 0; i < linhas_B; i++) {
    for (int j = 0; j < colunas_B; j++) {
      fprintf(arquivo_matriz, "b%d%d ", i+1, j+1);
      fprintf(arquivo_matriz,"%d \n", matriz_B[i][j]);
    }
  }
  fprintf(arquivo_matriz, "\n");

  fclose(arquivo_matriz);
  return 0;
}
