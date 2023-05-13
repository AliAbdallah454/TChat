#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main(){
	try{

		boost::asio::io_context io_context;
		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 22222));

		tcp::socket socket(io_context);
		acceptor.accept(socket);

		cout << "Client is connected" << endl;

		char buffer[512] = {0};

		while (true){
			memset(buffer, 0, sizeof(buffer));
			size_t length = boost::asio::read(socket, boost::asio::buffer(buffer));
			cout << string(buffer, length) << endl;
		}
	}
	catch (std::exception &e){
		cerr << "Exception: " << e.what() << endl;
	}

	return 0;

}
