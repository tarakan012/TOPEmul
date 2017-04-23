#include "stdafx.h"
#include "SubMap.h"

bool CSubMap::Enter(Square * pSEntShape, CEntity * ent, cLong clSearchRadius)
{
	const Point l_pt = pSEntShape->centre;
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

	return false;
}

Rect CSubMap::GetEyeshot(Point & pt) const
{
	const Rect & m_area = GetRange();
	Rect l_rect;
	pt.x = (pt.x - m_area.ltop.x) / GetEyeshotCellWidth();
	pt.y = (pt.y - m_area.ltop.y) / GetEyeshotCellHeight();
	l_rect.ltop.x = std::max(pt.x-GetEyeshotWidth(),(long)0);
	l_rect.ltop.y = std::max(pt.y - GetEyeshotWidth(), (long)0);
	l_rect.rbtm.x = std::max(pt.x + GetEyeshotWidth(), (long)0);//--
	l_rect.rbtm.y = std::max(pt.x + GetEyeshotWidth(), (long)0);//--

	return l_rect;
}

Rect CSubMap::GetRange() const
{
	return m_pCMapRes->GetRange();
}
