#pragma once

class CTableCha
{
public:
	CTableCha(pqxx::connection * pPQCon);
	bool ReadAllData(CPlayer * pCPlayer, DWORD dwChaID);
public:
	pqxx::connection * m_pPQCon;
};

class CGameDB
{
public:
	
	BOOL Init();
	bool ReadAllData(CPlayer * pCPayer, DWORD dwChaID);
	CGameDB();
protected:
	CTableCha * pCTabCha;
	pqxx::connection * m_pPQCon;

};

extern CGameDB g_gamedb;
