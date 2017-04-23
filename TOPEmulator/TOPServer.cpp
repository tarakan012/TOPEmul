#include "TOPServer.h"

TOPServer::TOPServer()
	: TCPServer(2)
{
}
bool TOPServer::Init()
{
	TCPServer::set_top_server(this);
	TCPServer::start_server(1973);
	return true;
}
//TOPServer & TOPServer::GetInstance()
//{
//	return 
//}

//void TOPServer::OnProccesData(RPacket & rpkt, TCPSession * tcpses)
//{
//	uShort l_cmd = 0;
//	uShort l_version = 0;
//	l_cmd = rpkt.readCmd();
//	switch (l_cmd)
//	{
//	case CMD_CS_LOGOUT:
//	{
//		tcpses->close();
//		break;
//	}
//	case CMD_CS_BGNPLAY:
//	{
//		CCharacter l_cha;
//		WPACKET wpkt;
//		l_cha.Cmd_EnterMap(wpkt);
//		tcpses->SendData(wpkt);
//		break;
//	}
//	case CMD_CS_LOGIN:
//	{
//		l_version = rpkt.reverseReadShot();
//		uShort l_errno;
//		if (l_version != 136)
//		{
//			return;
//		}
//		m_AccAuth.queryAccount(m_player, rpkt);
//		WPACKET wpkt;
//		wpkt = m_AccAuth.accountLogin();
//		if (l_errno = RPacket(wpkt).readShort())
//		{
//			wpkt.WriteCmd(CMD_SC_LOGIN);
//			tcpses->SendData(wpkt);
//			this->close();
//			return;
//		}
//		cChar l_key[] = { 0x00, 0x08, 0x7C, 0x35, 0x09, 0x19, 0xB2, 0x50, 0xD3, 0x49 };
//		wpkt.WriteSequence(l_key, 10); // 
//		GetChaFromDB(m_player, wpkt);
//		BYTE byPassword = 1;
//		/*if (m_player->m_password == "0")
//		{
//		byPassword = 0;
//		}*/
//		wpkt.WriteCmd(CMD_SC_LOGIN); //+
//		wpkt.WriteChar(byPassword); //+
//		wpkt.WriteLong(em_comm_enc); //+
//		wpkt.WriteLong(0x3214); //+
//		tcpses->SendData(wpkt);
//
//		break;
//	}
//	case CMD_CS_CREATE_PASSWORD2:
//	{
//		WPACKET wpkt;
//		string strPassword = rpkt.ReadString();
//		m_tblaccounts.UpdatePassword(m_player->m_acctLoginID, strPassword);
//		wpkt.WriteCmd(CMD_SC_CREATEPASSWORD2);
//		wpkt.WriteShort(ERR_SUCCESS);
//		tcpses->SendData(wpkt);
//		break;
//	}
//	/*case CMD_CS_UPDATE_PASSWORD2:
//	{
//	WPACKET wpkt;
//	string strPassword = rpkt.ReadString();
//	m_tblaccounts.UpdatePassword(m_player->m_acctLoginID, strPassword);
//	wpkt.WriteCmd(CMD_SC_CREATEPASSWORD2);
//	wpkt.WriteShort(ERR_SUCCESS);
//	sendData(wpkt);
//	break;
//	}*/
//	case CMD_CS_NEWCHA:
//	{
//		uShort	l_len = 0;
//		cChar * l_chaname = rpkt.ReadString(l_len);
//		cChar * l_birth = rpkt.ReadString(l_len);
//		string strName(l_chaname);
//		string strBirth(l_birth);
//		const LOOK * look = reinterpret_cast<const LOOK*>(rpkt.readSequence(l_len));
//		if (l_len != sizeof(LOOK))
//		{
//
//		}
//		char l_look[2048];
//		LookDataString(look, l_look);
//		m_tblcharacters.InsertRow(strName, strBirth, l_look);
//		m_tblcharacters.FetchRowByChaName(strName);
//		string strChaIDs;
//		if (m_tblaccounts.m_chaIDs == "0")
//		{
//			strChaIDs = to_string(m_tblcharacters.m_chaid) + ";";
//		}
//		else
//		{
//			strChaIDs = m_tblaccounts.m_chaIDs + to_string(m_tblcharacters.m_chaid) + ";";
//		}
//
//		m_player->m_chaid[m_player->m_chanum] = m_tblcharacters.m_chaid;
//		m_tblaccounts.UpdateRow(m_player->m_acctLoginID, strChaIDs);
//		WPACKET wpkt;
//		wpkt.WriteShort(ERR_SUCCESS);
//		wpkt.WriteCmd(CMD_SC_NEWCHA);
//		tcpses->SendData(wpkt);
//		break;
//	}
//	default:
//	{
//		break;
//	}
//	}
//}
