#pragma once

#include "Packet.h"
#include "AccountServer.h"

class TCPSession : public std::enable_shared_from_this<TCPSession>
{
public:
	~TCPSession();
	TCPSession(boost::asio::io_service & service);
	boost::asio::ip::tcp::socket & socket()
	{
		return socket_;
	}
	std::string getPeerIP()
	{
		return socket_.remote_endpoint().address().to_string();
	}
	 //WPacket & _onConnected() { return gs_.onConnected(); };
	// void _onProccesData(RPacket & rpkt) { gs_.onProccesData(rpkt); };

	void start();
	void sendData(WPacket & wpkt);
	void read_packet_len();
	void read_packet();
	void onProccesData(RPacket & rpkt);
	void onConnected(WPacket & lpkt);
	bool getChaFromDB(WPacket & pkt);
	char * get_receive_buffer()
	{
		return receive_buffer_.get();
	}
	void disconect()
	{
		socket_.close();
	}
private:
	asio::io_service & service_;
	asio::ip::tcp::socket socket_;
	std::unique_ptr<char[]> receive_buffer_;
	AuthThread m_AccAuth;
	TBLAccounts m_tblaccounts;
	uShort m_version;
	std::string m_str_time;
};