#pragma once

#include "TCPSession.h"


class TOPServer;
class TCPServer 
{
	using shared_handler_t = std::shared_ptr<TCPSession>;
public:
	TCPServer(int thread_count = 1)
		: thread_count_(thread_count)
		, acceptor_(io_service_)
	{}
	void start_server(uShort port = 1973);
	void set_top_server(TOPServer * topsvr){}
	void handle_new_connection(shared_handler_t hadler
		, system::error_code const & error);
private:
	int thread_count_;
	std::vector<std::thread> thread_pool_;
	std::vector<TCPSession*> tcp_session_pool_;
	asio::io_service io_service_;
	asio::ip::tcp::acceptor acceptor_;
	TOPServer * top_svr_;
};