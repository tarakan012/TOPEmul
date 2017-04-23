#pragma once
#include "ItemContent.h"

#pragma pack(push,1)
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
			USHORT sHairID;
		};
		struct
		{
			USHORT sPosID;		
			USHORT sBoatID;
			USHORT sHeader;		
			USHORT sBody;		
			USHORT sEngine;			
			USHORT sCannon;			
			USHORT sEquipment;			
		};
	};
} LOOK;
#pragma pack(pop)

enum EMoveState
{
	enumMSTATE_ON = 0x01,
	enumMSTATE_ARRIVE = 0x01
};

enum EActionType
{
	enumACTION_NONE = 0,
	enumACTION_MOVE
};

enum EEntitySeenType
{
	enameNTITY_SEEN_NEW = 0
};

enum EPoseState
{
	enumPoseStand = 0
};