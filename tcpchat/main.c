#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "servidor.h"
#include "cliente.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <cliente(c)/servidor(s)> {<host>} <puerto>\n", argv[0]);
        exit(1);
    }
    if (strcmp(argv[1], "s") == 0) {
        servidor(argv[2]);
    }
    if (strcmp(argv[1], "c") == 0) {
        cliente(argv[2], argv[3]);
    }

    return 0;
}
