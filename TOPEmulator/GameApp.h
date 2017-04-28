#pragma once

class CMapRes;
class CGameApp
{
public:
	using NameMapRes = map<string, CMapRes *>;

	bool Init();
	bool InitMap();

	CMapRes * FindMapByName(string mapname);
	void AddPlayer(DWORD dwDBID, CPlayer * pPlayer);
	CPlayer * GetPlayerByDBID(DWORD dwDBID);
	CPlayer * CreateGamePlayer(DWORD ulChaID);
	void ProcessPacket(TCPSession * pCSession, RPACKET & rpk);
private:
	NameMapRes m_MapList;
	map<DWORD, CPlayer *> m_PlayerIdx;
};

extern CGameApp * g_pCGameApp;

void g_GameLogicProcess();
