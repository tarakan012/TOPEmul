
#include "GameApp.h"

CMapRes * CGameApp::FindMapByName(std::string mapname)
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

