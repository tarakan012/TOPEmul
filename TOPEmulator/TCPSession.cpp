#include "stdafx.h"
#include "TCPSession.h"

char pong[] = { '0','2','\0' };

void TCPSession::start()
{
	BOOST_LOG_TRIVIAL(debug) << "IP: " << socket_.remote_endpoint().address().to_string() << " Port: " << socket_.remote_endpoint().port();
	onConnected();
	read_packet_len();
}

void TCPSession::sendData(WPacket & wpkt)
{
	asio::async_write(socket_, asio::buffer(wpkt.getPktAddr(), wpkt.getPktLen()), [](
		boost::system::error_code const & error, size_t bytes_xfer){});
}

void TCPSession::read_packet_len()
{
	async_read(socket_, asio::buffer(receive_buffer_.get(), 2)
		, [my = shared_from_this()](
		  boost::system::error_code const & error, size_t bytes_xfer){
		my->read_packet();
	});
}

void TCPSession::read_packet()
{

	uShort datalen = 0;
	memcpy((char*)&datalen, receive_buffer_.get(), 2);
	boost::endian::endian_reverse_inplace<uShort>(datalen);
	std::cout << "datalen: " << datalen;
	if (datalen == 2)
	{
		boost::asio::async_write(socket_, asio::buffer(pong, 2), [my = shared_from_this()](
		  boost::system::error_code const & error, size_t bytes_xfer){
		my->read_packet_len();});
	} else
	{
		RPacket l_rpkt;
		async_read(socket_, asio::buffer(const_cast<char*>(l_rpkt.getDataAddr()), datalen), [my=shared_from_this(), &l_rpkt](boost::system::error_code const & error, size_t bytes_xfer)
		{/*my->onProccesData(l_rpkt);*/ });
		
	}
}

