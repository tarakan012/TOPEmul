#pragma once

#include "stdafx.h"
#include "Packet.h"

class TCPSession : public std::enable_shared_from_this<TCPSession>
{
public:
	TCPSession(boost::asio::io_service & service)
		: service_(service)
		, work_(service_)
		, socket_(service)
		, write_strand_(service)
		, receive_buffer_(new char[64 * 1024]())
	{}
	boost::asio::ip::tcp::socket & socket()
	{
		return socket_;
	}
	virtual void onConnected() {};
	virtual void onProccesData(RPacket & rpkt) {};

	void start();
	void sendData(WPacket & wpkt);
	void read_packet_len();
	void read_packet();
private:
	asio::io_service & service_;
	asio::ip::tcp::socket socket_;
	asio::io_service::strand write_strand_;
	std::unique_ptr<char> receive_buffer_;
	asio::io_service::work work_;
};