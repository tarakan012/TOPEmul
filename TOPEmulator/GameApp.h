#pragma once

#include "MapRes.h"
#include<string>
#include<map>

class CGameApp
{
public:
	using NameMapRes = std::map<std::string, CMapRes *>;
	CMapRes * FindMapByName(std::string mapname);
	bool InitMap();
	void AddPlayer(DWORD dwDBID, CPlayer* pPlayer);
	CPlayer* GetPlayerByDBID(DWORD dwDBID);
private:
	NameMapRes m_MapList;
	std::map<DWORD, CPlayer*> m_PlayerIdx;
};

extern CGameApp * g_pCGameApp;