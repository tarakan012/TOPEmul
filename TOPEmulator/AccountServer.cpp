#include "AccountServer.h"
#include "crypt.h"
using namespace std;



void AuthThread::queryAccount(RPacket & rpkt,std::string & stime)
{
	cChar * pName = nullptr;
	cChar * pPass = nullptr;
	string szLocale = "";
	uShort usBufLen = 0;

	szLocale = rpkt.readString(); //
	pName = rpkt.readString();
	pPass = rpkt.readSequence(usBufLen);

	string strMAC = rpkt.readString();
	//BOOST_LOG_TRIVIAL(debug) << "PASSWD " << strEncodePass;
	m_AcctInfo.strName = pName;
	m_AcctInfo.strEncodePwd = pPass;
	m_AcctInfo.strChapString = stime;
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("SELECT * FROM public.user where login=" + pqwk.quote(m_AcctInfo.strName));
	if (!pqres.empty())
	{
		m_AcctInfo.bExist = true;
		//m_AcctInfo.nStatus = pqres[0]["login_status"].as<uShort>();
		//m_AcctInfo.nId = pqres[0]["id"].as<uShort>();
		m_AcctInfo.strPwdDigest = pqres[0]["password"].as<string>();
	//	BOOST_LOG_TRIVIAL(warning) << "NO USERNAME " << strUserName;

	}
	else
	{
		m_AcctInfo.bExist = false;
	}
}

WPacket AuthThread::accountLogin()
{
	WPacket wpkt;
	wpkt.writeCmd(0);
	if (!m_AcctInfo.bExist)
	{
		wpkt.writeShort(ERR_SC_INVALIDUSER);
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
		wpkt.writeShort(ERR_SC_INVALIDPWD); // если убрать, то все ломается
		return wpkt;
	}
	wpkt.writeShort(ERR_SUCCESS);
	return wpkt;
}
	

