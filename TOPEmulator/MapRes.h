#pragma once

#include "EyeshotCell.h"
//#include "SubMap.h"
class CSubMap;
class CMapRes
{
public:
	enum{ m_emeyeshotwidth = 2 };
	//CMapRes();
	void Init();
	Rect GetRange()const { return m_SRange; }
	CSubMap * GetCopy(void)const { return m_pCMapCopy; }
	cShort m_csEyeshotCellWidth{ 800 };
	cShort m_csEyeshotCellHeight{ 800 };
private:
	Rect m_SRange;
	CSubMap * m_pCMapCopy;

};