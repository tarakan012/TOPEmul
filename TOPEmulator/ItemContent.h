#pragma once

#include "ItemAttr.h"

#pragma pack(push,2)
struct SItemGrid
{
	bool IsInstAttrValid(void) { return sInstAttr[0][0] > 0 ? true : false; }
	long GetDBParam(short m) { return lDBParam[m]; }
	void SetDBParam(short sDBParam, long lDBParamVal)
	{
		lDBParam[sDBParam] = lDBParamVal;
		bChange = true;
	}
	short sID;
	short sNum;
	short sEndure[2];
	short sEnergy[2];
	char chForgeLv;
	long lDBParam[2];
	short sInstAttr[5][2];
	CItemAttr CAttr;
	bool bValid;
	bool bChange;
};
#pragma pack(pop)
