#include "TCPServer.h"

void TCPServer::start_server(uShort port)
{
	auto handler = std::make_shared<TCPSession>(io_service_);
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

void TCPServer::handle_new_connection(shared_handler_t hadler, system::error_code const & error)
{
	if (error)
	{
		return;
	}
	hadler->Start(top_svr_);
	auto new_handler = std::make_shared<TCPSession>(io_service_);

	acceptor_.async_accept(new_handler->socket(), [=](auto ec)
	{
		handle_new_connection(new_handler, ec);
	});
}