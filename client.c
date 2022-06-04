#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 32
#define PORT 80

char request[] = "GET / HTTP/1.0\n\n";

int main() {
    int sd, size, code;
    FILE *fout, *fin;
    struct addrinfo hints, *res;
    char buffer[SIZE];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    code = getaddrinfo("www.google.com", "80", &hints, &res);

    sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(sd, res->ai_addr, res->ai_addrlen);

    while( (size=read(STDIN_FILENO, buffer, SIZE)) > 0) {
        write(sd, buffer, size);
    }

    while( (size=read(sd, buffer, SIZE)) > 0) {
        write(1, buffer, size);
        printf("\n");
    }

    printf("\n\nFin del mensaje recibido\n");

    close(sd);
    freeaddrinfo(res);
}
