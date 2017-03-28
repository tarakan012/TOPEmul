#include "TCPSession.h"
#include "DataTimeToString.h"

char pong[] = { '0','2','\0' };

TCPSession::~TCPSession()
{
}

TCPSession::TCPSession(boost::asio::io_service & service)
	: service_(service)
	, work_(service)
	, socket_(service)
	
	, receive_buffer_(new char[64 * 1024]())

{
	m_str_time = "";
	m_version = 136;
}
void TCPSession::start()
{
	//BOOST_LOG_TRIVIAL(debug) << "IP: " << getPeerIP() << " Port: " << socket_.remote_endpoint().port();
	WPacket l_wpt;
	onConnected(l_wpt);
	sendData(l_wpt);
	read_packet_len();
}

void TCPSession::sendData(WPacket & wpkt)
{
	wpkt.writeSESS(128);
	wpkt.writePktLen();
	asio::async_write(socket_, asio::buffer(wpkt.getPktAddr(), wpkt.getPktLen()), [](
		boost::system::error_code const & error, size_t bytes_xfer){});
}

void TCPSession::read_packet_len()
{
	receive_buffer_.reset(new char[2]());
	async_read(socket_, asio::buffer(receive_buffer_.get(), 2)
		, [my = shared_from_this()](
			boost::system::error_code const & error, size_t bytes_xfer){
				my->read_packet();
	});
}

void TCPSession::read_packet()
{
	uShort l_pktlen = 0;
	memcpy((char*)&l_pktlen, receive_buffer_.get(), sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(l_pktlen);
	cout << "Len: " << l_pktlen << endl;
	if (l_pktlen == 2)
	{
		boost::asio::async_write(socket_, asio::buffer(pong, 2)
			, [my = shared_from_this()](
				boost::system::error_code const & error, size_t bytes_xfer){
					my->read_packet_len();
		});
	} else
	{
		async_read(socket_, asio::buffer(receive_buffer_.get() + 2, l_pktlen - 2)
			, [my=shared_from_this(), l_pktlen](boost::system::error_code const & error, size_t bytes_xfer)
		{
			RPacket l_rpkt;
			memcpy(const_cast<char*>(l_rpkt.getPktAddr()), my->receive_buffer().get(), l_pktlen);
			l_rpkt.setPktLen(l_pktlen);
			my->onProccesData(l_rpkt);
			//my->read_packet_len();
		});
	}
}

void TCPSession::onProccesData(RPacket & rpkt)
{
	uShort l_cmd = 0;
	uShort l_version = 0;
	l_cmd = rpkt.readCmd();
	switch (l_cmd)
	{
	case CMD_CS_LOGIN: {
		l_version = rpkt.reverseReadShot();
		uShort l_errno;
		if (m_version != l_version)
		{
			return;
		}
		m_AccAuth.queryAccount(rpkt, m_str_time);
		WPacket wpkt;
		wpkt = m_AccAuth.accountLogin();
		
		RPacket rpkt;
		rpkt = wpkt;
		if (rpkt.hasData())
		{

		}
		if (l_errno=rpkt.readShort())
		{
			wpkt.writeCmd(CMD_SC_LOGIN);
			sendData(wpkt);
			disconect();
		}
		wpkt.writeCmd(CMD_SC_LOGIN);
		cChar l_key[] = { 0x00, 0x08, 0x7C, 0x35, 0x09, 0x19, 0xB2, 0x50, 0xD3, 0x49 };
		wpkt.writeSequence(l_key, 10);
		break;
	}
	default:
		break;
	}
}

void TCPSession::onConnected(WPacket & lpkt)
{
	lpkt.writeCmd(CMD_SC_CHAPSTR);
	m_str_time = dataTimeToString(now(), "[%m-%d %H:%M:%S:100]"); // milisecond?
	lpkt.writeString(m_str_time.c_str());
}

bool TCPSession::getChaFromDB(WPacket & pkt)
{
	return false;
}

