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
  int **matriz_a;
  int linhas_a = atoi(argv[1]);
  int colunas_a = atoi(argv[2]);
  matriz_a = malloc(sizeof(int *) * linhas_a);
  for (int i = 0; i < linhas_a; i++) {
    matriz_a[i] = malloc(sizeof(int *) * colunas_a);
  }

  // Matriz B
  int **matriz_b;
  int linhas_b = atoi(argv[3]);
  int colunas_b = atoi(argv[4]);
  matriz_b = malloc(sizeof(int *) * linhas_b);
  for (int i = 0; i < linhas_b; i++) {
    matriz_b[i] = malloc(sizeof(int *) * colunas_b);
  }

  // Preenchimento aleatório de matrizes
  for (int i = 0; i < linhas_a; i++) {
    for (int j = 0; j < colunas_a; j++) {
      matriz_a[i][j] = rand() % 10;
    }
  }

  for (int i = 0; i < linhas_b; i++) {
    for (int j = 0; j < colunas_b; j++) {
      matriz_b[i][j] = rand() % 10;
      printf(" ");
    }
    printf(" \n ");
  }

  FILE *arquivo_matriz_a, *arquivo_matriz_b;
  arquivo_matriz_a = fopen("matriz_a.txt", "w");
  arquivo_matriz_b = fopen("matriz_b.txt", "w");

  // Escrevendo as linhas e colunas da matriz
  fprintf(arquivo_matriz_a, "%d %d\n", linhas_a, colunas_a);

  // Escrevendo os valores da matriz
  for (int i = 0; i < linhas_a; i++) {
    for (int j = 0; j < colunas_a; j++) {
      fprintf(arquivo_matriz_a, "a %d %d %d\n", i+1, j+1, matriz_a[i][j]);
    }
  }

  fprintf(arquivo_matriz_b, "%d %d\n", linhas_b, colunas_b);
  for (int i = 0; i < linhas_b; i++) {
    for (int j = 0; j < colunas_b; j++) {
      fprintf(arquivo_matriz_b, "b %d %d %d\n", i+1, j+1, matriz_b[i][j]);
    }
  }

  // Liberando as memórias das matrizes e fechando o arquivo
  for (int i = 0; i < linhas_a; i++) free(matriz_a[i]);
  free(matriz_a);
  for (int i = 0; i < linhas_b; i++) free(matriz_b[i]);
  free(matriz_b);
  fclose(arquivo_matriz_b);

  return 0;
}
