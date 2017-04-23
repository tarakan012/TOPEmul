#include "stdafx.h"
#include "FightAble.h"

void CFightAble::WriteAttr(WPACKET & pk, short sStartAttr, short sEndAttr, short sSynType)
{
	short sAttrChangeNum = 0;
	WRITE_CHAR(pk, sSynType);
	WRITE_SHORT(pk, sAttrChangeNum);
}
void CFightAble::WriteAttr(WPACKET & pkt, int nSynType)
{
	WRITE_CHAR(pkt, nSynType);
	WRITE_SHORT(pkt, 0);

}