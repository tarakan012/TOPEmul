#pragma once

#include "MapRes.h"
#include<string>
#include<map>

class CGameApp
{
public:
	using NameMapRes = std::map<std::string, CMapRes *>;
	CMapRes * FindMapByName(std::string mapname);
	bool IniMap();
private:
	NameMapRes m_MapList;
};

extern CGameApp * g_pCGameApp;