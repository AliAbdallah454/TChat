#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>

typedef struct AcceptClientsThreadArgs{
    int *clientSockets;
    int clientSocketsSize;
    int server_socker;
}AcceptClientsThreadArgs;

typedef struct BroadcastThreadArgs{
    int broadcasterSocket;
    int serverSocket;
    int *clientSockets;
    int clientSocketSize;
}BroadcastThreadArgs;

void *broadcast(void *threadArgs){

    BroadcastThreadArgs *args = (BroadcastThreadArgs *)threadArgs;

    char buffer[256];
    while(1){
        memset(buffer, 0, sizeof(buffer));
        recv(args->broadcasterSocket, buffer, sizeof(buffer), 0);

        for(int i = 0; i < args->clientSocketSize; i++){
            if(args->clientSockets[i] != 0){
                send(args->clientSockets[i], buffer, sizeof(buffer), 0);
            }
        }

    }

    pthread_exit(NULL);

}

void *acceptClients(void *threadArgs){

    AcceptClientsThreadArgs *args = (AcceptClientsThreadArgs*) threadArgs;

    int i = 0;

    while(1){
        int client_socket = accept(args->server_socker, NULL, NULL);
        args->clientSockets[i] = client_socket;
        i++;

        BroadcastThreadArgs broadcastThreadArgs;
        broadcastThreadArgs.broadcasterSocket = client_socket;
        broadcastThreadArgs.serverSocket = args->server_socker;
        broadcastThreadArgs.clientSockets = args->clientSockets;
        broadcastThreadArgs.clientSocketSize = args->clientSocketsSize;

        pthread_t broadcastThread;
        pthread_create(&broadcastThread, NULL,  broadcast, (void *)&broadcastThreadArgs);

    }

    pthread_exit(NULL);

}

int main(){

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket,(struct sockaddr *) &server_address, sizeof(server_address));
    listen(server_socket, 10);

    int client_sockets[10] = {0};

    AcceptClientsThreadArgs acceptClientsThreadArgs;
    acceptClientsThreadArgs.clientSockets = client_sockets;
    acceptClientsThreadArgs.clientSocketsSize = 10;
    acceptClientsThreadArgs.server_socker = server_socket;

    pthread_t acceptClientsThread;
    pthread_create(&acceptClientsThread, NULL, acceptClients, (void *)&acceptClientsThreadArgs);

    while(client_sockets[0] == 0){
        sleep(1);
    }
    printf("Someone is connected\n");   
    
    pthread_join(acceptClientsThread, NULL);
    close(server_socket);

    return 0;

}