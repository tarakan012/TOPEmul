#include "GameApp.h"
#include "GameDB.h"
#include "TCPSession.h"
#include "Character.h"
#include "MapRes.h"
#include "SubMap.h"

bool g_GameEnd = false;

CMapRes * CGameApp::FindMapByName(string mapname)
{
	auto result = m_MapList.find(mapname);
	if (result != m_MapList.end())
	{
		return result->second;
	}
	return nullptr;
}

bool CGameApp::InitMap()
{
	auto l_MapRes = new CMapRes();
	m_MapList.insert(NameMapRes::value_type("garner", l_MapRes ));
	return false;
}

bool CGameApp::Init()
{
	g_gamedb.Init();
	this->InitMap();
	return false;
}

void CGameApp::AddPlayer(DWORD dwDBID, CPlayer * pPlayer)
{
	m_PlayerIdx.insert(std::map<DWORD, CPlayer*>::value_type{dwDBID, pPlayer});
}

CPlayer * CGameApp::GetPlayerByDBID(DWORD dwDBID)
{
	auto result = m_PlayerIdx.find(dwDBID);
	if (result != m_PlayerIdx.end())
	{
		return result->second;
	}
	return nullptr;
}

CPlayer * CGameApp::CreateGamePlayer(DWORD ulChaID)
{
	CPlayer * l_pCPlayer = GetPlayerByDBID(ulChaID);
	g_gamedb.ReadAllData(l_pCPlayer, ulChaID);
	return l_pCPlayer;
}

void CGameApp::ProcessPacket(TCPSession * pCSession, RPACKET & rpk)
{
	CPlayer * l_player = 0;
	uShort l_cmd = READ_CMD(rpk);
	switch (l_cmd)
	{
	case CMD_CS_BGNPLAY :
	{
		l_player = pCSession->GetPlayer();
		CCharacter * pCCha = l_player->GetCtrlCha();
		pCCha->SetID(l_player->m_chaid[1]);

		g_gamedb.ReadAllData(l_player, pCCha->GetID());
		pCCha->Cmd_EnterMap(WPACKET());
		break;
	}
	default:
		break;
	}
}

void g_GameLogicProcess()
{
	cout << "Start g_GameLogicProcess" << endl;
	CSubMap * pCMap = 0;
	CMapRes * pCMapRes = 0;
	pCMapRes = g_pCGameApp->FindMapByName("garner");
	pCMap = pCMapRes->GetCopy();
	short l_EntCount;
	CEntity * pCEnt = 0;//
	CCharacter * pCCha;
	while(!g_GameEnd)
	{
		DWORD dwLastTick = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
		for (short x = 0; x < 36; x++)
		{
			for (short y = 0; y < 36; y++)
			{
				l_EntCount = pCMap->m_pCEyeshotCell[x][y].m_lChaCount;
				if (l_EntCount > 0)
				{
					pCCha = pCMap->m_pCEyeshotCell[x][y].m_ChaList[0];
					pCCha->OnMove(dwLastTick);
				}
			}
		}
	}
	cout << "End g_GameLogicProcess" << endl;

}



