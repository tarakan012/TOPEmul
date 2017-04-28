#pragma once
#include "Kitbag.h"
#include "MoveAble.h"
#include "Action.h"

class CCharacter : public CMoveAble
{
public:
	CCharacter();
	
	void ProcessPacket(uShort usCmd, RPACKET rpk);
	void AfterStepMove(void);
	void WriteSkillbag(WPACKET & pkt, int nSynType);
	void WriteSkillState(WPACKET & pkt);
	void WriteBaseInfo(WPACKET & pkt);
	void WriteLookData(WPACKET & wpkt, char chLookType, char chSynType);
	void WriteKitbug(CKitbag * pCkb, WPACKET & wpkt, int nSynType);
	void WriteBoat(WPACKET & wpkt);
	void WriteShortcut(WPACKET & wpkt);
	void WriteAppendLook(CKitbag * pCkb, WPACKET & wpkt, bool bInit);
	virtual void ReflectINFof(CMoveAble * pMoveAble, WPACKET & pk);
	virtual CCharacter * IsCharacter() { return this; }
	bool Cmd_EnterMap(WPACKET & wpkt);
	bool Cmd_BeginMove(short sPing, Point * pPoint, char chPointNum, char chStopState = '\001');
	void BeginAction(RPACKET & pk);
	void OnBeginSeen(CCharacter * pCCha);
	void OnEndSeen(CCharacter* pCCha);
	CPlayer * GetPlayer() { return m_pPlayer; }
	void SetPlayer(CPlayer * pPly) { m_pPlayer = pPly; }
protected:
	DWORD m_dwLastSayTick;
private:
	CAction m_CAction;
	CPlayer *  m_pPlayer;

};


