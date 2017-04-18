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
