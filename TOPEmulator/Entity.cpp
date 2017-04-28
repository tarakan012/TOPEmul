#include "Entity.h"
#include "SubMap.h"
#include "GameApp.h"
#include "Character.h"
#include "TCPSession.h"
#include "GameServerApp.h"

void CEntity::NotiChgToEyeshot(WPACKET & pk)
{
	CCharacter * pCSrcCha = this->IsCharacter();
	CEntity * pCTrgEnt = nullptr;
	short l_EntNum = 0;
	vector<CCharacter *> l_ChaList;
	CSubMap * pCMap = nullptr;
	CMapRes * pCMapRes = g_pCGameApp->FindMapByName("garner");
	pCMap = pCMapRes->GetCopy();
	Point l_pos = pCSrcCha->GetPos();//l_pos 224700 270400
	Rect l_rect = pCMap->GetEyeshot(l_pos);
//	for (short x = l_rect.ltop.x; x < l_rect.rbtm.x; ++x)
//	{
//		for (short y = l_rect.ltop.y; y < l_rect.rbtm.y; ++y)
//		{
////			l_EntNum = pCMap->m_pCEyeshotCell[x][y].m_ChaList.size();
//			l_EntNum = pCMap->m_pCEyeshotCell[x][y].m_lChaCount;
//			for (size_t i = 0; i < l_EntNum; i++)
//			{
//			pCTrgEnt = pCMap->m_pCEyeshotCell[x][y].m_ChaList.at(i);
//			l_ChaList.push_back(pCTrgEnt->IsCharacter());
//
//			}
//		}
//	}
	uShort l_cmd = 0;
	l_cmd = RPACKET(pk).ReadCmd();

	switch (l_cmd)
	{
	case CMD_SC_NOTIACTION:
	{
		for (auto & elem : l_ChaList)
		{
			if (elem == pCSrcCha)
			{
				pk.WriteLongByIndex(elem->m_ulPacketID, 12);
			}
			else
			{
				pk.WriteLongByIndex(elem->m_ulPacketID + 1, 12);
			}
		}
		break;
	}
	default:
		break;
	}
	l_ChaList.push_back(pCSrcCha);
	pk.WriteLongByIndex(pCSrcCha->m_ulPacketID, 12);
	
	GameServerApp::SendToClient(pk, l_ChaList);
}
