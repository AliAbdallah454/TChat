#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string.h>

int configSocket(){

    int sock1 = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(sock1, (struct sockaddr *) &server_address, sizeof(server_address));
    return sock1;
}

void sendMessage(int socket, char *message, char *name){
        char newMessage[512] = {0};
        strcat(newMessage, name);
        strcat(newMessage, " >> ");
        strcat(newMessage, message);
        newMessage[strcspn(newMessage, "\n")] = '\0';
        size_t message_size = strlen(newMessage);
        send(socket, newMessage, message_size, 0);
}