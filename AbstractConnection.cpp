//
// Created by jin on 12/21/18.
//

#include "AbstractConnection.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio.hpp>

static std::string make_daytime_string()
{
	std::time_t now = std::time(nullptr);
	char *cur_time = std::ctime(&now);
	return std::string(cur_time, strlen(cur_time) - 1);
}

AbstractConnection::AbstractConnection(boost::asio::io_service &io_service)
: socket_(io_service), chunk_to_send_(false)
{}

boost::asio::ip::tcp::socket &AbstractConnection::socket() {
	return socket_;
}

void AbstractConnection::start() {
	std::cout << "["<< make_daytime_string() << "] Incoming connection from "
			  << socket_.remote_endpoint().address().to_string() << std::endl;
	recv();
}

void AbstractConnection::send(const uint8_t *buf, size_t len ) {

	dispatch_send_(buf, len);
}

void AbstractConnection::recv() {
	dispatch_recv();
}

void AbstractConnection::set_send_status(bool status) {
	chunk_to_send_ = status;
}

void AbstractConnection::dispatch_send_(const uint8_t *buf, size_t len)
{
	memset(buf_send_, 0, buf_size_);
	memcpy(buf_send_, buf, len);
	start_send_(buf_send_, len);
}

void AbstractConnection::dispatch_recv() {
	memset(buf_recv_, 0, buf_size_);
	start_recv_();
}

void AbstractConnection::start_send_(const uint8_t *buf, size_t len) {
	if (chunk_to_send_ && len != 0) {
		boost::asio::async_write(socket_, boost::asio::buffer(buf, len),
								 boost::bind(&AbstractConnection::handle_send_, shared_from_this(),
								 boost::asio::placeholders::error, len));
	} else {
		start_recv_();
	}
}

void AbstractConnection::start_recv_() {
	socket_.async_read_some(boost::asio::buffer(buf_recv_, buf_size_),
							boost::bind(&AbstractConnection::handle_recv_, shared_from_this(),
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred));
}

void AbstractConnection::handle_send_(const boost::system::error_code &error, size_t len) {
	if (!error) {
		chunk_to_send_ = false;
		on_send(buf_send_, len);
		start_send_(buf_send_, len);
	}
	else {
		std::cout << "["<< make_daytime_string() << "] Send failed, error #" << error << " peer disconnected." << std::endl;
	}
}

void AbstractConnection::handle_recv_(const boost::system::error_code &error, size_t len){
	if (!error) {
		on_recv(buf_recv_, len);
	}
	else {
		std::cout << "["<< make_daytime_string() << "] Recv failed, error #" << error << " peer disconnected." << std::endl;
	}
}
