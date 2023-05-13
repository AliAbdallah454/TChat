// #include <ncurses.h>
#include <boost/asio.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <thread>

#include "boostClient.hpp"

using boost::asio::ip::tcp;
using namespace std;

int main(){

    char name[256] = "Ali";
    char message[256] = {0};

    tcp::socket socket = configSocket();

    while(true){

        cout << " >> ";
        fgets(message, sizeof(message), stdin);

        sendMessage(socket, name, message);

        memset(message, 0, sizeof(message));

    }    

    return 0;

}