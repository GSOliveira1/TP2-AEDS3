#include <limits.h>
#include <stdlib.h>
#include "estrategia2.h"

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}


int solucao1(int **matriz, int linhas, int colunas, int i, int j)
{
    if (i == linhas - 1 && j == colunas - 1)
    {
        return matriz[i][j] > 0 ? 1 : -matriz[i][j] + 1; //se estivermos na ultima posicao, retornamos o maior valor entre 1 e a vida(energia) atual
    }

    if (i >= linhas || j >= colunas)
    {
        return INT_MAX; //se estivermos fora dos limites da matriz, retornamos INT_MAX
    }

    int life_right = solucao1(matriz, linhas, colunas, i, j + 1); //calculamos a vida no caminho a direita
    int life_down = solucao1(matriz, linhas, colunas, i + 1, j); //calculamos a vida no caminho abaixo

    int min_life = min(life_right, life_down); //calculamos o menor valor entre a vida a direita e a vida abaixo

    return max(min_life - matriz[i][j], 1); //retornamos o menor valor entre 1 e a vida atual
}

//liberar memoria alocada pra matriz
void liberarMatriz(int **matriz, int M){
    for (int i = 0; i < M; i++)
        free(matriz[i]);
    free(matriz);
}