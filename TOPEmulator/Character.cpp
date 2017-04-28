#include "Character.h"
#include "TCPSession.h"
void CCharacter::OnBeginSeen(CCharacter * pCCa)
{
	if (this == pCCa)
	{
		return;
		//throw std::invalid_argument("OnBeginSeen");
	}
	WPACKET pk;
	WRITE_CMD(pk, CMD_SC_CHABEGINSEE);
	WRITE_CHAR(pk, enumENTITY_SEEN_NEW);
	pCCa->WriteBaseInfo(pk);
	BYTE ByState = 0, byShowType = 0;
	WRITE_CHAR(pk, byShowType);
	WRITE_CHAR(pk, ByState);
	WRITE_SHORT(pk, enumPoseStand);
	WriteAttr(pk, 0, 70, 0);
	WriteSkillState(pk);
	ReflectINFof(this, pk);
}

void CCharacter::OnEndSeen(CCharacter * pCCha)
{
	WPACKET wpkt;
	WRITE_CMD(wpkt, CMD_SC_CHAENDSEE);
	WRITE_CHAR(wpkt, enumENTITY_SEEN_NEW);
	WRITE_LONG(wpkt, pCCha->GetID());
	ReflectINFof(this, wpkt);
}

void CCharacter::ReflectINFof(CMoveAble * pMoveAble, WPACKET & pk)
{
	m_pPlayer->GetSession()->sendData(pk);
}

void CCharacter::AfterStepMove(void)
{
	CSubMap * pCSubMap = GetSubMap();

}