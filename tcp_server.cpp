//
// Created by jin on 12/21/18.
//

#include "tcp_server.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

tcp_server::tcp_server(boost::asio::io_service &io_service)
: acceptor_(io_service){

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

void tcp_server::listen( const std::string & host, const uint16_t & port)
{
	boost::asio::ip::tcp::resolver resolver(acceptor_.get_io_service());
	boost::asio::ip::tcp::resolver::query query( host, boost::lexical_cast< std::string>( port ) );
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );
	acceptor_.open( endpoint.protocol() );
	acceptor_.set_option( boost::asio::ip::tcp::acceptor::reuse_address( false ) );
	acceptor_.bind( endpoint );
	acceptor_.listen( boost::asio::socket_base::max_connections );
	//StartTimer();
}

void tcp_server::accept() {
	start_accept_();
}