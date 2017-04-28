#pragma once

//#include "TCPSession.h"

class CCharacter;
class CPlayer
{
	//~CPlayer();
	friend class TCPSession;
public:
	short FindIndexByChaName(string chaname);
	TCPSession * GetSession() { return m_session; }
	void SetSession(TCPSession * pSess) { m_session = pSess; }
	CCharacter * GetCtrlCha(void)const { return m_CCtrlCha.get(); }
	void SetCtrlCha(CCharacter * pCCtrlCha) { m_CCtrlCha.reset(pCCtrlCha); }
	CCharacter * GetMainCha(void)const { return m_CCtrlCha.get(); }
	void SetMainCha(CCharacter * pCCtrlCha) { m_CCtrlCha.reset(pCCtrlCha); }
	string m_strtime;
	string m_actname;
	string m_password;
	string m_chaname[3];
	char m_chanum;
	short m_bpcurrcha;
	int m_chaid[3];
	//short m_actid;
	short m_acctLoginID;
	bool m_bNew;
private:
	TCPSession * m_session;
	std::auto_ptr<CCharacter> m_CCtrlCha;
	std::auto_ptr<CCharacter> m_CMainCha;
};
