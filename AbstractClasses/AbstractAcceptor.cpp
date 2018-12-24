//
// Created by jin on 12/21/18.
//

#include "AbstractAcceptor.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

AbstractAcceptor::AbstractAcceptor(boost::asio::io_service &io_service)
: acceptor_(io_service){

}

void AbstractAcceptor::start_accept_()
{
	Connection::shd_ptr new_connection =
			Connection::create(acceptor_.get_io_service());

	acceptor_.async_accept(new_connection->socket(),
						   boost::bind(&AbstractAcceptor::handle_accept,
						   this, new_connection,
						   boost::asio::placeholders::error));
}

void AbstractAcceptor::handle_accept(Connection::shd_ptr new_connection,
							const boost::system::error_code &error)
{
	if (!error)
	{
		new_connection->start();
		start_accept_();
	}
}

void AbstractAcceptor::listen( const std::string & host, const uint16_t & port)
{
	boost::asio::ip::tcp::resolver resolver(acceptor_.get_io_service());
	boost::asio::ip::tcp::resolver::query query(host, boost::lexical_cast< std::string>(port));
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );
	acceptor_.open( endpoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen(boost::asio::socket_base::max_connections);
	//StartTimer();
}

void AbstractAcceptor::accept() {
	start_accept_();
}