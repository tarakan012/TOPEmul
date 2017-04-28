#include "MapRes.h"
#include"SubMap.h"
CMapRes::CMapRes()
{
	m_pCMapCopy = new CSubMap();
}

void CMapRes::Init()
{
	m_SRange.ltop.x = 0;
	m_SRange.ltop.y = 0;
	m_SRange.rbtm.x = 10000;
	m_SRange.rbtm.y = 10000;

}
