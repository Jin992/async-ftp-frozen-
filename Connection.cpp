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

void Connection::on_send(const char *buf, size_t len) {
	std::cout << "buffer [" << std::string(buf, len - 2)
				<< "] is send with len " << len << std::endl;
}

void Connection::on_recv(const char *buf, size_t buf_len) {
	std::string recv(buf, buf_len);
	if (recv == "ls\r\n"){
		std::cout << "["<< make_daytime_string()
					<< "][ls] control stream request from "
					<< socket().remote_endpoint().address().to_string()
					<< std::endl;
		set_send_status(true);
		send("ls\r\n", 4);
	}
}

Connection::Connection(boost::asio::io_service &io_service)
: AbstractConnection(io_service)
{}