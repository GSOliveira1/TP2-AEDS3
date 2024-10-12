#include "estrategia2.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char **argv) {
    //mesma estrutura utilizada no codigo da estrategia1.c para ler o arquivo, criar um novo arquivo e exibir o tempo de execucao e o uso de memoria no terminal
    struct timeval start, end;
    struct rusage usage;

    gettimeofday(&start, NULL);
    getrusage(RUSAGE_SELF, &usage);
    
    char *input = NULL;
    int option;

    while ((option = getopt(argc, argv, "i:o:")) != -1){
        switch (option)
        {
        case 'i':
            input = optarg;
            break;
        default:
            fprintf(stderr, "Opcao invalida ou faltando argumento: %c\n", optopt);
            return 1;
        }
    }

    if (input == NULL){
        printf("Opcao -i eh obrigatoria\n");
        return 1;
    }
    
    FILE *entrada = fopen(input, "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int* t = (int*)malloc(sizeof(int));

    fscanf(entrada, "%d", t);

    FILE *saida = fopen("saida.txt", "w");
    if (saida == NULL) {
        printf("Erro ao criar o arquivo de saida.\n");
        return 1;
    }



    for(int i = 0; i < *t; i++){

        int r, c;
        fscanf(entrada, "%d %d", &r, &c);

        int **matriz_principal = (int **)malloc(r * sizeof(int *));
        for (int i = 0; i < r; i++) {
            matriz_principal[i] = (int *)malloc(c * sizeof(int));
        }

        for (int i = 0; i < r; i++){
            for (int j = 0; j < c; j++){
                fscanf(entrada, "%d", &matriz_principal[i][j]);
            }
        }

        int energia_min;

        energia_min = solucao1(matriz_principal, r, c, 0, 0);


        fprintf(saida, "%d\n", energia_min);
    }
    
    free(t);
    fclose(entrada);
    fclose(saida);

    gettimeofday(&end, NULL);
    getrusage(RUSAGE_SELF, &usage);

    double tempo_exec = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Tempo de execucao: %.6f segundos\n", tempo_exec);

    printf("Uso de memoria: %ld kilobytes\n", usage.ru_maxrss);


    return 0;

}

