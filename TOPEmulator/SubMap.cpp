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
	//GoOut(ent);
	return false;
}

Rect CSubMap::GetEyeshot(Point & pt) const
{
	Rect area{ {0,0} ,{10000,10000} };
	//const Rect & m_area = GetRange();
	Rect l_rect;
	pt.x = (pt.x - area.ltop.x) / 30000;// GetEyeshotCellWidth();
	pt.y = (pt.y - area.ltop.y) / 30000;//GetEyeshotCellHeight();
	l_rect.ltop.x = max(pt.x - 2/*GetEyeshotWidth()*/,(long)0);
	l_rect.ltop.y = max(pt.y - 2, (long)0);
	l_rect.rbtm.x = max(pt.x + 2, (long)0);//--
	l_rect.rbtm.y = max(pt.y + 2, (long)0);//--

	return l_rect;
}

Rect CSubMap::GetRange() const
{
	return m_pCMapRes->GetRange();
}

void CSubMap::MoveTo(CEntity * pCEnt, Point pSTar)
{
	Point l_src = pCEnt->GetPos();
	Point l_dst = pSTar;
	Rect l_srcEyeshot = GetEyeshot(l_src);
	Rect l_dstEyeshot = GetEyeshot(l_dst);
	long l_xmax = max(l_srcEyeshot.rbtm.x, l_dstEyeshot.rbtm.x);
	long l_xmin = min(l_srcEyeshot.ltop.x, l_dstEyeshot.ltop.x);
	long l_ymax = max(l_srcEyeshot.rbtm.y, l_dstEyeshot.rbtm.y);
	long l_ymin = min(l_srcEyeshot.ltop.y, l_dstEyeshot.ltop.y);
	pCEnt->SetPos(pSTar);
	if (l_src != l_dst)
	{
		m_pCEyeshotCell[l_src.x][l_src.y].DelEntity(pCEnt);
		for (long x = l_xmin; x <= l_xmax; x++)
		{
			for (long y = l_ymin; y <= l_ymax; y++)
			{
				if ((abs(x - l_src.x) <= 2) && (abs(y - l_src.y) <= 2))
				{
					m_pCEyeshotCell[x][y].EnterEyeshot(pCEnt);
					//m_pCEyeshotCell[x][y].OutEyeshot(pCEnt);
				}
				else
				{
				}
			}
		}

		m_pCEyeshotCell[l_dst.x][l_dst.y].AddEntity(pCEnt->IsCharacter());
	}

}

void CSubMap::GoOut(CEntity * pCEnt)
{
	Point l_pos = pCEnt->GetPos();
	Rect l_rect = GetEyeshot(l_pos);
	for (long y = l_rect.ltop.y; y < l_rect.rbtm.y; y++)
	{
		for (long x = l_rect.ltop.x; x < l_rect.rbtm.x; x++)
		{
			m_pCEyeshotCell[x][y].OutEyeshot(pCEnt);
		}
	}
}