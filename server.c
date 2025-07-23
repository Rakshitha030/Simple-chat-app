#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[MAXLINE];
    int addrlen = sizeof(address);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // Listen
    listen(server_fd, 3);
    printf("Waiting for client to connect...\n");

    // Accept
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    printf("Client connected.\n");

    while (1) {
        bzero(buffer, MAXLINE);
        read(new_socket, buffer, sizeof(buffer));
        printf("Client: %s", buffer);

        bzero(buffer, MAXLINE);
        printf("Server: ");
        fgets(buffer, MAXLINE, stdin);
        send(new_socket, buffer, strlen(buffer), 0);
    }

    close(server_fd);
    return 0;
}
