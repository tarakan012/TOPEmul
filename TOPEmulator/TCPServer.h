#pragma once

#include "TCPSession.h"

template <class ConnectHundler>
class TCPServer 
{
	using shared_handler_t = std::shared_ptr<ConnectHundler>;
public:
	TCPServer(int thread_count = 1)
		: thread_count_(thread_count)
		, acceptor_(io_service_)
	{}
	void start_server(uShort port = 1973);
	void handle_new_connection(shared_handler_t hadler
		, system::error_code const & error);
private:
	int thread_count_;
	std::vector<std::thread> thread_pool_;
	asio::io_service io_service_;
	asio::ip::tcp::acceptor acceptor_;
};


template <class ConnectHundler>
inline void TCPServer<ConnectHundler>::start_server(uShort port)
{
	auto handler = std::make_shared<ConnectHundler>(io_service_);
	// set up acceptor to listen on the tcp port
	asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();

	acceptor_.async_accept(handler->socket(), [=](auto ec)
	{
		handle_new_connection(handler, ec);
	});
	for (size_t i = 0; i < thread_count_; ++i)
	{
		thread_pool_.emplace_back([=] { io_service_.run(); });
	}
}

template <class ConnectHundler>
inline void TCPServer<ConnectHundler>::handle_new_connection(shared_handler_t hadler, system::error_code const & error)
{
	if (error)
	{
		return;
	}
	hadler->start();
	auto new_handler = std::make_shared<ConnectHundler>(io_service_);

	acceptor_.async_accept(new_handler->socket(), [=](auto ec)
	{
		handle_new_connection(new_handler, ec);
	});

}