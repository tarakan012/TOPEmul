#include "Character.h"

void CCharacter::WriteSkillbag(WPACKET & pkt, int nSynType)
{
	WRITE_SHORT(pkt, 0);
	WRITE_CHAR(pkt, nSynType);

	WRITE_SHORT(pkt, 0);
}
void CCharacter::WriteSkillState(WPACKET & pkt)
{
	WRITE_CHAR(pkt, 0); 

}
void CCharacter::WriteAttr(WPACKET & pkt, int nSynType)
{
	WRITE_CHAR(pkt, nSynType);
	WRITE_SHORT(pkt, 0);

}
void CCharacter::WriteBaseInfo(WPACKET & pkt)
{
	WRITE_LONG(pkt, 4); //cat 
	WRITE_LONG(pkt, 123); //id
	WRITE_LONG(pkt, 123); //id
	WRITE_STRING(pkt, "tarakan"); //name
	WRITE_CHAR(pkt, 25346); // gmlvl
	WRITE_LONG(pkt, 11437); //handle
	WRITE_CHAR(pkt, 1); //chatype
	WRITE_STRING(pkt, "name");
	WRITE_STRING(pkt, "motto");
	WRITE_SHORT(pkt, 4); //icon
	WRITE_LONG(pkt, 1);//guildid
	WRITE_STRING(pkt, "guildname");
	WRITE_STRING(pkt, "guildmotto");
	WRITE_STRING(pkt, "stallname");
	WRITE_SHORT(pkt, 1);//existstate
	WRITE_LONG(pkt, 224700);//x
	WRITE_LONG(pkt, 270400);//y
	WRITE_LONG(pkt, 40);//radius
	WRITE_SHORT(pkt, 0);//angle
	WRITE_LONG(pkt, 0);//idtaemlider
	//writesideinfo
	WRITE_CHAR(pkt, 0); // sideid
	//writeeventinfo
	WRITE_LONG(pkt, 123); //id
	WRITE_CHAR(pkt, 1);
	//cevent::writeinfo
	WRITE_SHORT(pkt, 0); //m_usID
	WRITE_STRING(pkt, "name");
	WriteLookData(pkt,0,0);
	//writePKCtrl
	WRITE_CHAR(pkt, 0);
	CKitbag l_kitbag;
	WriteAppendLook(&l_kitbag, pkt, true);


}

void CCharacter::WriteLookData(WPACKET & wpkt, char chLookType, char chSynType)
{
	//writelookdata
	WRITE_CHAR(wpkt, chSynType);//sintype
	WRITE_SHORT(wpkt, 1); //typeid

	WRITE_CHAR(wpkt, 0);//
	WRITE_SHORT(wpkt, 2291); //hairid
	SItemGrid * pItem = new SItemGrid;
	memset((char*)pItem, 0, sizeof(SItemGrid));
	for (size_t i = 0; i < 10; i++)
	{
		WRITE_SHORT(wpkt, pItem->sID);

	}
}

void CCharacter::WriteKitbug(CKitbag * pCkb, WPACKET & wpkt, int nSynType)
{
	WRITE_CHAR(wpkt, nSynType);
	WRITE_SHORT(wpkt, 48); //pKb->capacity
	WRITE_SHORT(wpkt, -1); //pKb->capacity

}
void CCharacter::WriteBoat(WPACKET & wpkt)
{
	WRITE_CHAR(wpkt, 0);

}
void CCharacter::WriteShortcut(WPACKET & wpkt)
{
	for (size_t i = 0; i < 36; i++)
	{
		WRITE_CHAR(wpkt, 0);
		WRITE_SHORT(wpkt, 0); 
	}
}
void CCharacter::WriteAppendLook(CKitbag * pCkb, WPACKET & wpkt, bool bInit)
{
	SItemGrid * pGridCont;
	for (size_t i = 0; i < 4; i++)
	{
		WRITE_SHORT(wpkt, 0);

	}
}
