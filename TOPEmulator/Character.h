#pragma once
#include "Kitbag.h"

class CCharacter
{
public:
	void WriteSkillbag(WPACKET & pkt, int nSynType);
	void WriteSkillState(WPACKET & pkt);
	void WriteAttr(WPACKET & pkt, int nSynType);
	void WriteBaseInfo(WPACKET & pkt);
	void WriteLookData(WPACKET & wpkt, char chLookType, char chSynType);
	void WriteKitbug(CKitbag * pCkb, WPACKET & wpkt, int nSynType);
	void WriteBoat(WPACKET & wpkt);
	void WriteShortcut(WPACKET & wpkt);
	void WriteAppendLook(CKitbag * pCkb, WPACKET & wpkt, bool bInit);
	bool Cmd_EnterMap(WPACKET & wpkt);
};


