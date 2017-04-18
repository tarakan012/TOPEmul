#include "TCPSession.h"
#include "Character.h"

#include "DataTimeToString.h"
#include "CommFunc.h"
#include <regex>

char pong[] = { '0','2'};

enum{ em_comm_enc = 0 };

void outHexByCout(const char* cha, int len)
{
	for (size_t i = 0; i < len; ++i)
	{
		cout  << setw(2) << setfill('0') << hex << static_cast<uShort>(static_cast<unsigned char>(cha[i])) << " ";
	}
	cout << endl;
}

TCPSession::~TCPSession()
{
}

TCPSession::TCPSession(boost::asio::io_service & service)
	: service_(service)
	, socket_(service)
	, receive_buffer_(new char[64 * 1024]())
	, m_player(nullptr)
{

}
void TCPSession::start()
{
	//BOOST_LOG_TRIVIAL(debug) << "IP: " << getPeerIP() << " Port: " << socket_.remote_endpoint().port();
	WPACKET l_wpt;
	onConnected(l_wpt);
	sendData(l_wpt);
	read_packet_len();
}

void TCPSession::onConnected(WPACKET & lpkt)
{
	m_player = new CPlayer;
	lpkt.WriteCmd(CMD_SC_CHAPSTR);
	m_player->m_strtime = dataTimeToString(now(), "[%m-%d %H:%M:%S:100]"); // milisecond?
	lpkt.WriteString(m_player->m_strtime.c_str());
}

void TCPSession::sendData(WPACKET & wpkt)
{
	wpkt.WriteSESS(128);
	wpkt.WritePktLen();
	outHexByCout(wpkt.getPktAddr(), wpkt.getPktLen());
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
	cout << "LEN: " << l_pktlen << endl;
	if (l_pktlen == 0) return;
	if (l_pktlen == 2)
	{
		boost::asio::async_write(socket_, asio::buffer(receive_buffer_.get(), 2)
			, [my = shared_from_this()](
				boost::system::error_code const & error, size_t bytes_xfer){
					my->read_packet_len();
		});
	} else
	{
		receive_buffer_.reset(new char[l_pktlen-2]());
		async_read(socket_, asio::buffer(receive_buffer_.get(), l_pktlen - 2)
			, [my=shared_from_this(), l_pktlen](boost::system::error_code const & error, size_t bytes_xfer)
		{
			RPacket l_rpkt;
			memcpy(const_cast<char*>(l_rpkt.getPktAddr()) + 2, my->get_receive_buffer(), l_pktlen - 2);
			l_rpkt.setPktLen(l_pktlen);
			l_rpkt.WritePktLen(l_pktlen);
			outHexByCout(l_rpkt.getPktAddr(), l_rpkt.getPktLen());
			my->OnProccesData(l_rpkt);
			my->read_packet_len();
		});
	}
}

void TCPSession::OnProccesData(RPacket & rpkt)
{
	uShort l_cmd = 0;
	uShort l_version = 0;
	l_cmd = rpkt.readCmd();
	switch (l_cmd)
	{
		case CMD_CS_LOGOUT :
		{
			this->close();
			break;
		}
		case CMD_CS_BGNPLAY:
		{
			CCharacter l_cha;
			WPACKET wpkt;
			l_cha.Cmd_EnterMap(wpkt);
			sendData(wpkt);
			break;
		}
		case CMD_CS_LOGIN : 
		{
			l_version = rpkt.reverseReadShot();
			uShort l_errno;
			if (l_version != 136)
			{
				return;
			}
			m_AccAuth.queryAccount(m_player, rpkt);
			WPACKET wpkt;
			wpkt = m_AccAuth.accountLogin();
			if (l_errno = RPacket(wpkt).readShort())
			{
				wpkt.WriteCmd(CMD_SC_LOGIN);
				sendData(wpkt);
				this->close();
				return;
			}
			cChar l_key[] = { 0x00, 0x08, 0x7C, 0x35, 0x09, 0x19, 0xB2, 0x50, 0xD3, 0x49 };
			wpkt.WriteSequence(l_key, 10); // 
			GetChaFromDB(m_player, wpkt);
			BYTE byPassword = 1; 
			if (m_player->m_password == "0")
			{
				byPassword = 0;
			}
			wpkt.WriteCmd(CMD_SC_LOGIN); //+
			wpkt.WriteChar(byPassword); //+
			wpkt.WriteLong(em_comm_enc); //+
			wpkt.WriteLong(0x3214); //+
			sendData(wpkt);

			break;
		}
		case CMD_CS_CREATE_PASSWORD2 :
		{
			WPACKET wpkt;
			string strPassword = rpkt.readString();
			m_tblaccounts.UpdatePassword(m_player->m_acctLoginID, strPassword);
			wpkt.WriteCmd(CMD_SC_CREATEPASSWORD2);
			wpkt.WriteShort(ERR_SUCCESS);
			sendData(wpkt);
			break;
		}
		/*case CMD_CS_UPDATE_PASSWORD2:
		{
			WPACKET wpkt;
			string strPassword = rpkt.readString();
			m_tblaccounts.UpdatePassword(m_player->m_acctLoginID, strPassword);
			wpkt.WriteCmd(CMD_SC_CREATEPASSWORD2);
			wpkt.WriteShort(ERR_SUCCESS);
			sendData(wpkt);
			break;
		}*/
		case CMD_CS_NEWCHA :
		{
			uShort	l_len = 0;
			cChar * l_chaname = rpkt.readString(l_len);
			cChar * l_birth = rpkt.readString(l_len);
			string strName(l_chaname);
			string strBirth(l_birth);
			const LOOK * look = reinterpret_cast<const LOOK*>(rpkt.readSequence(l_len));
			if (l_len != sizeof(LOOK)) 
			{

			}
			char l_look[2048];
			LookDataString(look, l_look);
			m_tblcharacters.InsertRow(strName, strBirth, l_look);
			m_tblcharacters.FetchRowByChaName(strName);
			string strChaIDs;
			if (m_tblaccounts.m_chaIDs == "0")
			{
				strChaIDs = to_string(m_tblcharacters.m_chaid) + ";";
			}
			else
			{
				strChaIDs = m_tblaccounts.m_chaIDs + to_string(m_tblcharacters.m_chaid) + ";";
			}

			m_player->m_chaid[m_player->m_chanam] = m_tblcharacters.m_chaid;
			m_tblaccounts.UpdateRow(m_player->m_acctLoginID, strChaIDs);
			WPACKET wpkt;
			wpkt.WriteShort(ERR_SUCCESS);
			wpkt.WriteCmd(CMD_SC_NEWCHA);
			sendData(wpkt);
			break;
		}
		default:
		{
			break;
		}
	}
}


bool TCPSession::GetChaFromDB(CPlayer * ply,WPACKET & pkt)
{
	short l_row = 0;
	if (l_row = m_tblaccounts.FetchRowByActName(ply->m_actname) == 0)
	{
		ply->m_bNew = true;
		pkt.WriteChar(0);
		m_tblaccounts.InsertRow(ply->m_acctLoginID, ply->m_actname, "0");
	}
	else
	{
		ply->m_bNew = false;
		std::regex regex("(\\d)+");
		string l_strChaIDs = m_tblaccounts.m_chaIDs;
		auto world_begin = std::sregex_iterator(l_strChaIDs.begin(), l_strChaIDs.end(), regex);
		auto world_end = std::sregex_iterator();
		ply->m_chanam = std::distance(world_begin,world_end);
		ply->m_password = m_tblaccounts.m_password;
		pkt.WriteChar(ply->m_chanam);
		for (size_t i = 0; i < ply->m_chanam; ++i)
		{
			ply->m_chaid[i] = SRegIterInt(world_begin++);
			if (!ply->m_chaid[i])
			{
				pkt.WriteChar(0);
			}
			else
			{
				if (m_tblcharacters.FetchRowByChaID(ply->m_chaid[i]) == 1);
				{
					LOOK l_look;
					memset((char*)&l_look, 0, sizeof(l_look));
					StringLookData(&l_look, m_tblcharacters.m_look);
					ply->m_chaname[i] = m_tblcharacters.m_chaname;
					pkt.WriteChar(1);
					pkt.WriteString(m_tblcharacters.m_chaname.c_str());
					pkt.WriteString(m_tblcharacters.m_job.c_str());
					pkt.WriteShort(m_tblcharacters.m_degree);
					pkt.WriteSequence((char*)&l_look, sizeof(l_look));
				}
			}
		}
	}
	return false;
}

