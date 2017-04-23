#pragma once

//#include "TCPSession.h"

using namespace std;

class CPlayer
{
	friend class TCPSession;
public:
	short FindIndexByChaName(string chaname);
	TCPSession * GetSession() { return m_session; }
	void SetSession(TCPSession * pSess) { m_session = pSess; }
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
};
