#pragma once

//#include "GameApp.h"
//#include "TCPSession.h"
//#include "Character.h"


//void CGameApp::ProcessPacket(TCPSession * pCSession, RPACKET & rpk)
//{
//	CPlayer * l_player = 0;
//	uShort l_cmd = READ_CMD(rpk);
//	switch (l_cmd)
//	{
//	case CMD_CS_BGNPLAY :
//	{
//		l_player = pCSession->GetPlayer();
//		CCharacter * pCCha = l_player->GetCtrlCha();
//		g_gamedb.ReadAllData(l_player, pCCha->GetID());
//		pCCha->Cmd_EnterMap(WPACKET());
//		break;
//	}
//	default:
//		break;
//	}
//}

