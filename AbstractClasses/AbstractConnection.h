//
// Created by jin on 12/21/18.
//

#ifndef ASIO_ASYNC_FTP_TCP_CONNECTION_H
#define ASIO_ASYNC_FTP_TCP_CONNECTION_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

class AbstractAcceptor;

class AbstractConnection: public boost::enable_shared_from_this<AbstractConnection> {
	friend class AbstractAcceptor;
public:
	explicit AbstractConnection(boost::asio::io_service &);
	virtual ~AbstractConnection() = default;

	void connect(const std::string & host,uint16_t port);
	void start();
	void recv();
	void send(const uint8_t *, size_t);
	void set_send_status(bool status);
	boost::asio::ip::tcp::socket &socket();

private:
	virtual void on_send(const uint8_t *, size_t) = 0;
	virtual void on_recv(const uint8_t *, size_t) = 0;
	virtual void on_connect(const std::string &host, uint16_t port) = 0;

private:
	void dispatch_send_(const uint8_t *, size_t);
	void dispatch_recv();
	void start_send_(const uint8_t *, size_t);
	void start_recv_();
	void handle_send_(const boost::system::error_code &, size_t);
	void handle_recv_(const boost::system::error_code &, size_t);
	void handle_connect(const boost::system::error_code & error);

	enum
	{
		buf_size_ = 1024
	};
	boost::asio::ip::tcp::socket socket_;
	uint8_t buf_recv_[buf_size_];
	uint8_t buf_send_[buf_size_];
	bool chunk_to_send_;


};


#endif //ASIO_ASYNC_FTP_TCP_CONNECTION_H
