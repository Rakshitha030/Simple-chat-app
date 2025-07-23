#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAXLINE];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);  // localhost

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    printf("Connected to server.\n");

    while (1) {
        bzero(buffer, MAXLINE);
        printf("Client: ");
        fgets(buffer, MAXLINE, stdin);
        send(sock, buffer, strlen(buffer), 0);

        bzero(buffer, MAXLINE);
        read(sock, buffer, sizeof(buffer));
        printf("Server: %s", buffer);
    }

    close(sock);
    return 0;
}
