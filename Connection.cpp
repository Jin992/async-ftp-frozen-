//
// Created by jin on 12/21/18.
//

#include "Connection.h"
#include <iostream>

static std::string make_daytime_string()
{
	std::time_t now = std::time(nullptr);
	char *cur_time = std::ctime(&now);
	return std::string(cur_time, strlen(cur_time) - 1);
}

Connection::shd_ptr Connection::create(boost::asio::io_service &io_service)
{
	return shd_ptr(new Connection(io_service));
}

void Connection::on_send(const unsigned char *buf, size_t len) {
	std::cout << "[" << len << "] bytes has been send." << std::endl;
}

void Connection::on_recv(const uint8_t *buf, size_t buf_len) {
	std::string recv(reinterpret_cast<const char *>(buf), buf_len);
	if (recv == "ls\r\n"){
		std::cout << "["<< make_daytime_string()
					<< "][ls] control stream request from "
					<< socket().remote_endpoint().address().to_string()
					<< std::endl;
		set_send_status(true);
		char answer[] = "ls\r\n";
		send(reinterpret_cast<const uint8_t *>(answer), 4);
	}
}

Connection::Connection(boost::asio::io_service &io_service)
: AbstractConnection(io_service)
{}