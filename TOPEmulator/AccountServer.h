#pragma once

#include "Packet.h"
#include "pqxx\pqxx"

using namespace std;

extern pqxx::connection * g_conpq;

struct AccountInfo
{
	uShort nStatus;
	uShort nId;
	string strName;
	bool bExist;
	string strPwdDigest;
	string strChapString;
	string strEncodePwd;
};

class AuthThread
{
public:
	AuthThread() {} //:g_conpq(new pqxx::connection("dbname=noterius user = nota host=127.0.0.1 password = notadefault")) {}
	void queryAccount(RPacket&, std::string&);
	WPacket accountLogin();
	//~AuthThread();

private:
	//pqxx::connection * g_conpq;
	AccountInfo m_AcctInfo;
};

class TBLAccounts
{
public:
	int fetchRowByActName(string account);
	bool updatePassword(int act_id, string password);
private:
};


