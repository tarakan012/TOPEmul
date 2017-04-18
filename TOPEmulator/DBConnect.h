#pragma once

class TBLAccounts
{
public:
	int FetchRowByActName(string act_name);
	bool InsertRow(int act_id, const string & act_name, const string & cha_id);
	bool UpdateRow(int act_id, const string & cha_ids);
	bool UpdatePassword(int act_id, string password);
	string m_chaIDs;
	string m_password;
};

class TBLCharacters
{
public:
	int FetchRowByChaID(int cha_id);
	int FetchRowByChaName(const string & cha_name);
	bool InsertRow(const string & cha_name, const string & birth, const char * look);
	string m_look;
	string m_job;
	string m_chaname;
	short m_degree;
	short m_chaid;
};
