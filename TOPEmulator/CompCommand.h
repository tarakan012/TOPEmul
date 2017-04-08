#pragma once

class CItemAttr
{
public:
	CItemAttr() { m_bInitFlug = false; sizeof(CItemAttr); }
private:
	short m_Attr[58];
	bool m_bInitFlug;

};


struct SItemGrid
{
	DWORD dwDBID;
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

typedef 
struct stNetChangeChaPart
{
	stNetChangeChaPart() { sVer = 0; sTypeID = 0; 	sizeof(SItemGrid);
	}
	short sVer;
	short sTypeID;
	union {
		struct {
			SItemGrid sLink[10];
			short sHairID;
		};
		struct
		{
			USHORT sPosID;		// 船动作ID
			USHORT sBoatID;				// 船信息表ID
			USHORT sHeader;				// 船头
			USHORT sBody;				// 船身
			USHORT sEngine;				// 船只马达
			USHORT sCannon;				// 船只火炮
			USHORT sEquipment;			// 船只装备
		};
	};
} LOOK;