#include <iostream>
#include "tcp_server.h"


int main() {
    try{
    	boost::asio::io_service io_service;
    	tcp_server server(io_service);

    	server.listen("127.0.0.1", 8081);
    	server.accept();

    	io_service.run();
    }
    catch (std::exception &e)
	{
    	std::cerr << e.what() << std::endl;
	}
    return 0;
}