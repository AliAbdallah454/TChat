#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>
#include <string.h>

int main(){

    int sock1 = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(sock1, (struct sockaddr *) &server_address, sizeof(server_address));

    if(connection_status == -1){
        printf("Opps, there was an error here\n");
    }

    //Sending and receiving

    char response[255] = {0};
    char message[255] = {0};
    // recv(sock1, response, sizeof(response), 0);
    // printf("response : %s\n", response);

    for(int i = 0; i < 5; i++){
        printf("in loop\n");
        fflush(stdout);
        // fgets(message, sizeof(message), stdin);
        scanf(message, "%s");
        send(sock1, message, sizeof(message), 0);
        printf("in loop end\n");
    }


    close(sock1);

    return 0;

}