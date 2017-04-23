#pragma once


#include "AccountServer.h"
#include "DBConnect.h"
//#include "TOPServer.h"

class TOPServer;
class TCPSession : public std::enable_shared_from_this<TCPSession>
{
public:
	TCPSession(boost::asio::io_service & service);
	void Start(TOPServer * topsvr);
	~TCPSession();
	boost::asio::ip::tcp::socket & socket()
	{
		return socket_;
	}
	std::string getPeerIP()
	{
		return socket_.remote_endpoint().address().to_string();
	}
	char * get_receive_buffer()
	{
		return receive_buffer_.get();
	}
	void close()
	{
		socket_.close();
	}
	void sendData(WPACKET & wpkt);
	void read_packet_len();
	void read_packet();
	void OnProccesData(RPacket & rpkt);
	void OnConnected(WPACKET & lpkt);
	bool GetChaFromDB(CPlayer * ply, WPACKET & pkt);
private:
	asio::io_service & service_;
	asio::ip::tcp::socket socket_;
	std::unique_ptr<char[]> receive_buffer_;
	AuthThread m_AccAuth;
	TBLAccounts m_tblaccounts;
	TBLCharacters m_tblcharacters;
	CPlayer * m_player;
	TOPServer * m_topsvr;
};