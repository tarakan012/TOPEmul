#pragma once

#include "Entity.h"
#include "MapRes.h"

class CSubMap
{
public:
	CSubMap();
	bool Enter(Square * pSEntShape, CEntity * ent, cLong clSearchRadius = 40 * 100);
	Rect GetEyeshot(Point & pt)const;
	short GetEyeshotCellWidth(void)const { return m_pCMapRes->m_csEyeshotCellWidth; }
	short GetEyeshotCellHeight(void)const { return m_pCMapRes->m_csEyeshotCellHeight; }
	short GetEyeshotWidth(void)const { return m_pCMapRes->m_emeyeshotwidth; }
	Rect GetRange()const;
	void MoveTo(CEntity * pCEnt, Point pSTar);
	void GoOut(CEntity * pCEnt);
	CEyeshotCell m_pCEyeshotCell[36][36];
private:
	CMapRes *  m_pCMapRes;
};
