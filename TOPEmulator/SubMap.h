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
private:
	CMapRes *  m_pCMapRes;
	CEyeshotCell m_pCEyeshotCell[30][30];
};
