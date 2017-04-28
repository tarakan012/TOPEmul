#include "AccountServer.h"
#include "crypt.h"


pqxx::connection * g_conpq = new pqxx::connection("dbname=noterius user = nota host=127.0.0.1 password = notadefault");

void AuthThread::queryAccount(CPlayer * ply, RPacket & rpkt)
{
	cChar * pName = nullptr;
	cChar * pPass = nullptr;
	string szLocale = "";
	uShort usBufLen = 0;

	szLocale = rpkt.ReadString(); //
	pName = rpkt.ReadString();
	pPass = rpkt.ReadSequence(usBufLen);

	string strMAC = rpkt.ReadString();
	ply->m_actname = m_AcctInfo.strName = pName;
	m_AcctInfo.strEncodePwd = pPass;
	m_AcctInfo.strChapString = ply->m_strtime;
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("SELECT * FROM public.account_login where login=" + pqwk.quote(m_AcctInfo.strName));
	if (!pqres.empty())
	{
		m_AcctInfo.bExist = true;
		//m_AcctInfo.nStatus = pqres[0]["login_status"].as<uShort>();
		//m_AcctInfo.nId = pqres[0]["id"].as<uShort>();
		m_AcctInfo.strPwdDigest = pqres[0]["password"].as<string>();
		ply->m_acctLoginID = pqres[0]["id"].as<short>();

	}
	else
	{
		m_AcctInfo.bExist = false;
	}
}

WPACKET AuthThread::accountLogin()
{
	WPACKET wpkt;
	wpkt.WriteCmd(0);
	if (!m_AcctInfo.bExist)
	{
		wpkt.WriteShort(ERR_SC_INVALIDUSER);
		return wpkt;
	}
	if (m_AcctInfo.nStatus == 0)
	{

	}
	else if (m_AcctInfo.nStatus == 1)
	{
			
	}
	string strEncryptPass = EncryptPassword(m_AcctInfo.strPwdDigest, m_AcctInfo.strChapString);
	if (m_AcctInfo.strEncodePwd != strEncryptPass)
	{
		wpkt.WriteShort(ERR_SC_INVALIDPWD); // если убрать, то все ломается
		return wpkt;
	}
	wpkt.WriteShort(ERR_SUCCESS);
	return wpkt;
}
	

