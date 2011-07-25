#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define TAM 256

void cliente(char * ip, int p) {
    int sockfd, puerto, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[TAM];

    puerto = atoi(p);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR apertura de socket");
        exit(1);
    }
    server = gethostbyname(ip);
    if (server == NULL) {
        fprintf(stderr, "Error, no existe el host\n");
        exit(0);
    }

    memset(&serv_addr, '0', sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(puerto);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        perror("conexion");
        exit(1);
    }

    while (1) {
        printf("Ingrese el mensaje a transmitir: ");
        memset(buffer, '0', TAM);
        fgets(buffer, TAM - 1, stdin);

        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("escritura de socket");
            exit(1);
        }

        memset(buffer, '\0', TAM);
        n = read(sockfd, buffer, TAM);
        if (n < 0) {
            perror("lectura de socket");
            exit(1);
        }
        printf("Respuesta: %s\n", buffer);
    }
};
