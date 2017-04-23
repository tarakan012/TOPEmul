#include "Character.h"
#include "TCPSession.h"

void CCharacter::OnBeginSeen(CCharacter * pCCa)
{
	WPACKET pk;
	WRITE_CMD(pk, CMD_SC_CHABEGINSEE);
	WRITE_CHAR(pk, enumENTITY_SEEN_NEW);
	WriteBaseInfo(pk);
	BYTE ByState = 0, byShowType = 0;
	WRITE_CHAR(pk, byShowType);
	WRITE_CHAR(pk, ByState);
	WRITE_SHORT(pk, enumPoseStand);
	WriteAttr(pk, 0, 70, 0);
	WriteSkillState(pk);
	ReflectINFof(this, pk);
}

void CCharacter::ReflectINFof(CMoveAble * pMoveAble, WPACKET & pk)
{
	m_pPlayer->GetSession()->sendData(pk);
}
