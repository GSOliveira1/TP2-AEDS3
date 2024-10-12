#include "estrategia1.h"
#include <stdio.h>
#include <stdlib.h>

//o calculo para obter a energia minima para chegar em determinada posicao eh melhor explicado na secao 2.2.2 da documentacao

//funcao pra preencher a primeira linha e a primeira coluna, ja que os elementos contidos nelas so podem ser acessados pelo movimento de ir pra dreita ou descer, respectivamente
void preencher_bordas_memin(int** matriz_principal, int** matriz_energia_min, int** m_saldo_energia, int m, int n){
    
    matriz_energia_min[0][0] = 1; //como a energia nao pode ser menor ou igual a 0, entao a energia minima para a primeira posicao sempre deve ser 1
    
    int* saldo_energia = (int*)malloc(sizeof(int));
    
    *saldo_energia = 1; 
    
    //calcula a energia minima da coluna 1
    for(int i = 1; i < m; i++){
        if(matriz_principal[i][0] >= 0){
            matriz_energia_min[i][0] = matriz_energia_min[i - 1][0];
            *saldo_energia += matriz_principal[i][0];
            m_saldo_energia[i][0] = *saldo_energia;
        }
        else if(matriz_principal[i][0] < 0){
            if((matriz_principal[i][0] * (-1)) + 1 > *saldo_energia){
                matriz_energia_min[i][0] = matriz_energia_min[i - 1][0] + ((matriz_principal[i][0] * (-1)) - *saldo_energia) + 1;
                *saldo_energia = 1;
                m_saldo_energia[i][0] = *saldo_energia;
            }
            else if((matriz_principal[i][0] * (-1)) + 1 == *saldo_energia){
                matriz_energia_min[i][0] = matriz_energia_min[i - 1][0];
                *saldo_energia = 1;
                m_saldo_energia[i][0] = *saldo_energia;
            }
            else{
                *saldo_energia += matriz_principal[i][0];
                matriz_energia_min[i][0] = matriz_energia_min[i - 1][0];
                m_saldo_energia[i][0] = *saldo_energia;
            }
        }
    }
    
    *saldo_energia = 1;
    
    //calcula a energia minima da linha 1
    for(int j = 1; j < n; j++){
        if(matriz_principal[0][j] >= 0){
            matriz_energia_min[0][j] = matriz_energia_min[0][j - 1];
            *saldo_energia += matriz_principal[0][j];
            m_saldo_energia[0][j] = *saldo_energia;
        }
        else if(matriz_principal[0][j] < 0){
            if((matriz_principal[0][j] * (-1)) + 1 > *saldo_energia){
                matriz_energia_min[0][j] = matriz_energia_min[0][j - 1] + ((matriz_principal[0][j] * (-1)) - *saldo_energia) + 1;
                *saldo_energia = 1;
                m_saldo_energia[0][j] = *saldo_energia;
            }
            else if((matriz_principal[0][j] * (-1)) + 1 == *saldo_energia){
                matriz_energia_min[0][j] = matriz_energia_min[0][j - 1];
                *saldo_energia = 1;
                m_saldo_energia[0][j] = *saldo_energia;
            }
            else{
                *saldo_energia += matriz_principal[0][j];
                matriz_energia_min[0][j] = matriz_energia_min[0][j - 1];
                m_saldo_energia[0][j] = *saldo_energia;
            }
        }
    }
}

 //funcao p/ encontrar o valor de energia minima p/ chegar na posicao i x j
int menor_energia_inicial(int** matriz_principal, int** matriz_energia_min, int** m_saldo_energia, int i, int j){

    //se o caminho vindo de cima possuir uma energia minima menor ou igual a do caminho vindo da esquerda
    if(matriz_energia_min[i - 1][j] <= matriz_energia_min[i][j - 1]){
        if(matriz_principal[i][j] < 0){
            if((matriz_principal[i][j] * (-1)) + 1 > m_saldo_energia[i - 1][j]){
                matriz_energia_min[i][j] = matriz_energia_min[i - 1][j] + ((matriz_principal[i][j] * (-1)) - m_saldo_energia[i - 1][j]) + 1;
                m_saldo_energia[i][j] = 1;
            }
            else if((matriz_principal[i][j] * (-1)) + 1 == m_saldo_energia[i - 1][j]){ //+ 1 porque sempre precisa ter 1 de energia p/ continuar
                matriz_energia_min[i][j] = matriz_energia_min[i - 1][j];
                m_saldo_energia[i][j] = 1; // 1 porque sempre precisa ter 1 de energia p/ continuar
            }
            else{
                m_saldo_energia[i][j] = m_saldo_energia[i - 1][j] + matriz_principal[i][j];
                matriz_energia_min[i][j] = matriz_energia_min[i - 1][j];
            }
        }
        else{
            matriz_energia_min[i][j] = matriz_energia_min[i - 1][j];
            m_saldo_energia[i][j] = m_saldo_energia[i - 1][j] + matriz_principal[i][j];
        }
    }

    //se o caminho vindo da esquerda possuir uma energia menor que o caminho vindo de cima
    else if(matriz_energia_min[i - 1][j] > matriz_energia_min[i][j - 1]){
        if(matriz_principal[i][j] < 0){
            if((matriz_principal[i][j] * (-1)) + 1 > m_saldo_energia[i][j - 1]){
                matriz_energia_min[i][j] = matriz_energia_min[i][j - 1] + ((matriz_principal[i][j] * (-1)) - m_saldo_energia[i][j - 1]) + 1;
                m_saldo_energia[i][j] = 1;
            }
            else if((matriz_principal[i][j] * (-1)) + 1 == m_saldo_energia[i][j - 1]){ 
                matriz_energia_min[i][j] = matriz_energia_min[i][j - 1];
                m_saldo_energia[i][j] = 1;
            }
            else{
                m_saldo_energia[i][j] = m_saldo_energia[i][j - 1] + matriz_principal[i][j];
                matriz_energia_min[i][j] = matriz_energia_min[i][j - 1];
            }
        }
        else{
            matriz_energia_min[i][j] = matriz_energia_min[i][j - 1];
            m_saldo_energia[i][j] = m_saldo_energia[i][j - 1] + matriz_principal[i][j];
        }
    }
    return matriz_energia_min[i][j];
}

//funcao p/ preencher a matriz_energia_min em que cadaa posicao M[i][j] armazena a energia minima para ser alcancada
void preencher_matriz_energia_min(int** matriz_principal, int** matriz_energia_min, int** m_saldo_energia, int m, int n){
    for(int i = 1; i < m; i++){
        for(int j = 1; j < n; j++){
            matriz_energia_min[i][j] = menor_energia_inicial(matriz_principal, matriz_energia_min,m_saldo_energia, i, j); 
        }
    }
}

//retorna a energia minima pra alcancar a ultima posicao
int menor_energia_inicial_matriz(int **matriz_energia_min, int m, int n){
    return matriz_energia_min[m - 1][n - 1];
}

//liberar memoria alocada pra matriz
void liberarMatriz(int **matriz, int M){
    for (int i = 0; i < M; i++)
        free(matriz[i]);
    free(matriz);
}

