//
// Created by jin on 12/21/18.
//

#include "tcp_server.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>

tcp_server::tcp_server(boost::asio::io_service &io_service, unsigned short port)
: acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
	start_accept_();
}

void tcp_server::start_accept_()
{
	Connection::shd_ptr new_connection =
			Connection::create(acceptor_.get_io_service());

	acceptor_.async_accept(new_connection->socket(),
						   boost::bind(&tcp_server::handle_accept,
						   this, new_connection,
						   boost::asio::placeholders::error));
}

void tcp_server::handle_accept(Connection::shd_ptr new_connection,
							const boost::system::error_code &error)
{
	if (!error)
	{
		new_connection->start();
		start_accept_();
	}
}