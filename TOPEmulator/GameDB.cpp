#include "GameDB.h"
//#include "Player.h"
#include "Character.h"

#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"

bool CGameDB::ReadAllData(CPlayer * pCPlayer, DWORD dwChaID)
{
	pCTabCha->ReadAllData(pCPlayer, dwChaID);
	return false;
}

CGameDB::CGameDB()
	: pCTabCha(nullptr)
	, m_pPQCon(nullptr)
{

}

BOOL CGameDB::Init()
{
	try {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("config.ini", pt);

		string dbname = pt.get<string>("Database.Name");
		string user = pt.get<string>("Database.User");
		string host = pt.get<string>("Database.IP");
		string password = pt.get<string>("Database.Password");

		cout << format("Connecting database [%s : %s]...") % host % dbname << endl;


		m_pPQCon = new pqxx::connection("dbname = " + dbname + " user = " + user + " host = " + host + " password = " + password);

		pCTabCha = new CTableCha(m_pPQCon);

		cout << "Database connected!" << endl;
	}
	catch (const std::exception & e)
	{
		cerr << "Error connection database: " << e.what() << endl;
		return false;
	}
	return true;
}

CTableCha::CTableCha(pqxx::connection * pPQCon)
	: m_pPQCon(pPQCon)
{

}
bool CTableCha::ReadAllData(CPlayer * pCPlayer, DWORD dwChaID)
{
	CCharacter * pCha = pCPlayer->GetMainCha();
	pqxx::work pqwk(*m_pPQCon);
	pqxx::result pqres = pqwk.exec("SELECT * FROM public.character WHERE cha_id=" + pqwk.quote(dwChaID));
	if (!pqres.empty())
	{
		pCha->SetName(pqres[0]["cha_name"].as<string>());
	}
	return false;
}

CGameDB g_gamedb;

