#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){

    char message[255] = "This is a message from the server\n";

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket,(struct sockaddr *) &server_address, sizeof(server_address));
    listen(server_socket, 3);

    int client_socket = accept(server_socket, NULL, NULL);

    // Sending an receiving

    // send(client_socket, message, sizeof(message), 0);

    char respond[200] = {0};
    for(int i = 0; i < 5; i++){
        recv(client_socket, respond, sizeof(respond), 0);
        printf("Client : %s\n", respond);
    }
    
    close(server_socket);

    return 0;

}