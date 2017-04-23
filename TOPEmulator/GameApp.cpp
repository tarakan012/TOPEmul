
#include "GameApp.h"

CMapRes * CGameApp::FindMapByName(std::string mapname)
{
	auto result = m_MapList.find(mapname);
	if (result != m_MapList.end())
	{
		return result->second;
	}
	return nullptr;
}

bool CGameApp::IniMap()
{
	auto l_MapRes = new CMapRes();
	m_MapList.insert(NameMapRes::value_type("garner", l_MapRes ));
	return false;
}

