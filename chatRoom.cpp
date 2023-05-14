#include <boost/asio.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <thread>

#include "boostClient.hpp"

using boost::asio::ip::tcp;
using namespace std;

void receiveAndPrint(tcp::socket &socket){

    char buffer[256] = {0};
    while(true){
        size_t length = socket.read_some(boost::asio::buffer(buffer));
        cout << "MESSAGE : " << string(buffer, length) << endl;
    }

}

int main(){

    tcp::socket socket = configSocket();

    thread receiveAndPrintThread(receiveAndPrint, ref(socket));

    char name[256] = {};
    char message[256] = {0};

    cout << "Enter name : ";
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    while(true){

        cout << " >> ";
        fgets(message, sizeof(message), stdin);
        
        if(message[0] == '\n') continue;
        sendMessage(socket, name, message);
        memset(message, 0, sizeof(message));

    }    

    receiveAndPrintThread.join();

    return 0;

}