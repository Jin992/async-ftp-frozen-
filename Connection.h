//
// Created by jin on 12/21/18.
//

#ifndef ASIO_ASYNC_FTP_CONNECTION_H
#define ASIO_ASYNC_FTP_CONNECTION_H
#include "AbstractConnection.h"

class Connection: public AbstractConnection {
public:
	typedef boost::shared_ptr<Connection> shd_ptr;

	static shd_ptr create(boost::asio::io_service &);
	void on_send(const uint8_t *, size_t) override;
	void on_recv(const uint8_t *, size_t) override;

private:
	explicit Connection(boost::asio::io_service &);
};


#endif //ASIO_ASYNC_FTP_CONNECTION_H
