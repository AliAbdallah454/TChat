#include <boost/asio.hpp>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>

#define BUFFER_SIZE 256

using namespace std;

using boost::asio::ip::tcp;

tcp::socket configSocket(){

    boost::asio::io_context io_contex;
    tcp::resolver resolver(io_contex);
    tcp::resolver::results_type endpoint = resolver.resolve("localhost", "22222");

    tcp::socket socket(io_contex);
    boost::asio::connect(socket, endpoint);

    return socket;

}

void sendMessage(tcp::socket &socket, char *name, char *message){

    message[strcspn(message, "\n")] = '\0';

    char messagePlusName[512] = {0};

    strcat(messagePlusName, name);
    strcat(messagePlusName, " >> ");
    strcat(messagePlusName, message);

    boost::asio::write(socket, boost::asio::buffer(messagePlusName, sizeof(messagePlusName)));

}