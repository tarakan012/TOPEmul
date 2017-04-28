#pragma once
#include "ChaAttr.h"
#include "Entity.h"

class CFightAble : public CEntity
{
public:
	void WriteAttr(WPACKET & pkt, int nSynType);

	void Test(){}
	void WriteAttr(WPACKET & pk, short sStartAttr, short sEndAttr, short sSynType);
	uLong m_ulPacketID;
private:
	CChaAttr m_CChaAttr;
};
