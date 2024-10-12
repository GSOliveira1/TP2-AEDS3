#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include "estrategia1.h"
#include "estrategia2.h"

// para verificar os argumentos e selecionar qual estrategia sera utilizada

int main(int argc, char *argv[]) {

    int option;

    char *input_file = NULL;

    while ((option = getopt(argc, argv, "i:o:")) != -1) {
        switch (option) {
            case 'i':
                input_file = optarg;
                break;
        }
    }

    switch (atoi(argv[optind])) {
        case 1:

            char *estrategia1_args[] = {"./estrategia1", "-i", input_file, NULL};
            execvp(estrategia1_args[0], estrategia1_args);

            fprintf(stderr, "Erro ao executar a estrategia 1.\n");
            return 1;

        case 2:

            char *estrategia2_args[] = {"./estrategia2", "-i", input_file, NULL};
            execvp(estrategia2_args[0], estrategia2_args);

            fprintf(stderr, "Erro ao executar a estrategia 2.\n");
            return 1;

        default:
            fprintf(stderr, "Opção inválida.\n");
            return 1;
    }

    return 0;
}
