#include "stdafx.h"
#include "SubMap.h"

CSubMap::CSubMap()
{
	//m_pCMapRes = new CMapRes();
}
bool CSubMap::Enter(Square * pSEntShape, CEntity * ent, cLong clSearchRadius)
{
	
	const Point l_pt = pSEntShape->centre;
	CCharacter * l_pCCha = ent->IsCharacter();
	Point l_pt1;
	l_pt1 = l_pt;
	Rect l_rect = GetEyeshot(l_pt1);
	for (long y = l_rect.ltop.y; y < l_rect.rbtm.y; y++)
	{
		for (long x = l_rect.ltop.x; x < l_rect.rbtm.x; x++)
		{
			m_pCEyeshotCell[x][y].EnterEyeshot(ent);
		}
	}
	m_pCEyeshotCell[l_pt1.x][l_pt1.y].AddEntity(l_pCCha);
	return false;
}

Rect CSubMap::GetEyeshot(Point & pt) const
{
	//const Rect & m_area = GetRange();
	Rect m_area{ {0,0} ,{10000,10000} };
	Rect l_rect;
	pt.x = (pt.x - m_area.ltop.x) / 8000;// GetEyeshotCellWidth();
	pt.y = (pt.y - m_area.ltop.y) / 8000;//GetEyeshotCellHeight();
	l_rect.ltop.x = std::max(pt.x - 2/*GetEyeshotWidth()*/,(long)0);
	l_rect.ltop.y = std::max(pt.y - 2, (long)0);
	l_rect.rbtm.x = std::max(pt.x + 2, (long)0);//--
	l_rect.rbtm.y = std::max(pt.x + 2, (long)0);//--

	return l_rect;
}

Rect CSubMap::GetRange() const
{
	return m_pCMapRes->GetRange();
}
