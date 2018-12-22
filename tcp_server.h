//
// Created by jin on 12/21/18.
//

#ifndef ASIO_ASYNC_FTP_TCP_SERVER_H
#define ASIO_ASYNC_FTP_TCP_SERVER_H

#include "Connection.h"

class tcp_server {
public:
	tcp_server(boost::asio::io_service &);
	void listen( const std::string &, const uint16_t &);

private:
	void start_accept_();
	void handle_accept(Connection::shd_ptr, const boost::system::error_code &);

private:
	boost::asio::ip::tcp::acceptor acceptor_;
};


#endif //ASIO_ASYNC_FTP_TCP_SERVER_H
