#include "DBConnect.h"
#include "AccountServer.h"

int TBLAccounts::FetchRowByActName(string act_name)
{
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("SELECT * FROM public.account where act_name=" + pqwk.quote(act_name));
	if (!pqres.empty())
	{
		m_chaIDs = pqres[0]["cha_ids"].as<string>();
		m_password = pqres[0]["password"].as<string>();
		return 1;
	}
	return 0;
}

bool TBLAccounts::InsertRow(int act_id, const string & act_name, const string & cha_id)
{
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("insert into public.account "
		"(act_id, act_name, cha_ids, password) "
		"values(" +
		pqwk.quote(act_id) + ", " +
		pqwk.quote(act_name) + ", " +
		pqwk.quote(cha_id) + ", " +
		pqwk.quote("0") +
		")"
	);
	pqwk.commit();
	return false;
}

bool TBLAccounts::UpdateRow(int act_id, const string & cha_ids)
{
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("UPDATE public.account SET cha_ids=" +
		pqwk.quote(cha_ids) + " WHERE act_id=" +
		pqwk.quote(act_id)
	);
	pqwk.commit();
	return false;
}

bool TBLAccounts::UpdatePassword(int act_id, string password)
{
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("UPDATE public.account SET password=" + pqwk.quote(password) + " where act_id=" + pqwk.quote(act_id));

	return true;
}

int TBLCharacters::FetchRowByChaID(int cha_id)
{
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("SELECT * FROM public.character where cha_id=" + pqwk.quote(cha_id));
	if (!pqres.empty())
	{
		m_look = pqres[0]["look"].as<string>();
		m_degree = pqres[0]["degree"].as<short>();
		m_job = pqres[0]["job"].as<string>();
		m_chaname = pqres[0]["cha_name"].as<string>();
		return 1;
	}
	return 0;
}

int TBLCharacters::FetchRowByChaName(const string & cha_name)
{
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("SELECT * FROM public.character where cha_name=" + pqwk.quote(cha_name));
	if (!pqres.empty())
	{
		m_chaid = pqres[0]["cha_id"].as<short>();
		return 1;
	}
	return 0;
}

bool TBLCharacters::InsertRow(const string & cha_name, const string & birth, const char * look)
{
	pqxx::work pqwk(*g_conpq);
	pqxx::result pqres = pqwk.exec("insert into public.character "
		"(cha_name, birth, look) "
		"values(" +
		pqwk.quote(cha_name) + ", " +
		pqwk.quote("Argent") + ", " +
		pqwk.quote(look) +
		")"
	);
	pqwk.commit();
	return false;
}
