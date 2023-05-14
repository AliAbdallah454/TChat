#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using boost::asio::ip::tcp;
using namespace std;

void gggg(tcp::socket &socket){

	char buffer[256] = "hello jeff";

	while(true){
		this_thread::sleep_for(chrono::seconds(2));
		boost::asio::write(socket, boost::asio::buffer(buffer));
	}
	
}

void printMessage(tcp::socket socket, vector<tcp::socket>& clients, mutex& clientMutex) {
    
    char buffer[256] = "Hello from the server";

	thread newThread(gggg, ref(socket));

    while (true) {
    	
		size_t length = socket.read_some(boost::asio::buffer(buffer));
		cout << string(buffer, length) << endl;
        memset(buffer, 0, sizeof(buffer));

    }
}

int main(){
	
	try{

		boost::asio::io_context io_context;
		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 22222));

		vector<tcp::socket> clients {};
		mutex clientMutex;

		vector<thread> threads;

		while (true) {

			tcp::socket socket(io_context);
			acceptor.accept(socket);

			cout << "- Client is connected" << endl;

			threads.emplace_back(printMessage, move(socket), ref(clients), ref(clientMutex));

		}

		for(auto &t : threads){
			t.join();
		}

	}
	catch (std::exception &e){
		cerr << "Exception: " << e.what() << endl;
	}
	
	return 0;

}