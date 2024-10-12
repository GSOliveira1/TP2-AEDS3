#ifndef ESTRATEGIA1_H
#define ESTRATEGIA1_H

void preencher_bordas_memin(int** matriz_principal, int** matriz_energia_min, int** m_saldo_energia, int m, int n);
int menor_energia_inicial(int **matriz_principal, int** matriz_energia_min, int** m_saldo_energia, int i, int j);
void preencher_matriz_energia_min(int** matriz_principal, int** matriz_energia_min, int** m_saldo_energia, int m, int n);
int menor_energia_inicial_matriz(int **matriz_energia_min, int m, int n);
void liberarMatriz(int **matriz, int linhas);

#endif