#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define TAM 256

void servidor(int p) {
    int sockfd, newsockfd, puerto, clilen, pid;
    char buffer[TAM];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror(" apertura de socket ");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof (serv_addr));
    puerto = atoi(p);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(puerto);


    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        perror("ligadura");
        exit(1);
    }

    printf("Socket disponible: %d\n", ntohs(serv_addr.sin_port));

    listen(sockfd, 5);
    clilen = sizeof (cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("accept");
            exit(1);
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            close(sockfd);
            while (1) {
                memset(buffer, 0, TAM);
                n = read(newsockfd, buffer, TAM - 1);
                if (n < 0) {
                    perror("lectura de socket");
                    exit(1);
                }

                printf("Recibí: %s", buffer);
                n = write(newsockfd, "Obtuve su mensaje", 18);
                if (n < 0) {
                    perror("escritura en socket");
                    exit(1);
                }
            }
            exit(0);
        } else {
            close(newsockfd);
        }
    }
};
