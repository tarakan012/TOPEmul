#include "Character.h"
#include "SubMap.h"
#include "MapRes.h"
#include "GameApp.h"
#include"TCPSession.h"
CCharacter::CCharacter()
	: m_CAction(this)
	, m_pPlayer(nullptr)
{

}
bool CCharacter::Cmd_EnterMap(WPACKET & wpkt)
{
	CSubMap * pCMap = 0;
	CMapRes * pCMapRes = 0;

	pCMapRes = g_pCGameApp->FindMapByName("garner");
	pCMap = pCMapRes->GetCopy();
	SetSubMap(pCMap);
	//WPACKET wpkt;
	WRITE_CMD(wpkt, CMD_SC_ENTERMAP);//+
	WRITE_SHORT(wpkt, ERR_SUCCESS);//+
	WRITE_CHAR(wpkt, 0);//autolook +
	WRITE_CHAR(wpkt, 0);//look +
	WRITE_CHAR(wpkt, 1);//entertype +
	WRITE_CHAR(wpkt, 0);//newcha +
	WRITE_STRING(wpkt,"garner");//+
	WRITE_CHAR(wpkt, 1);//can team +
	WriteBaseInfo(wpkt);//+
	WriteSkillbag(wpkt, 0);//+-
	WriteSkillState(wpkt);//+
	WriteAttr(wpkt,0);
	CKitbag l_kitbag;
	WriteKitbug(&l_kitbag,wpkt, 0);
	WriteShortcut(wpkt);
	//WRITE_LONG(wpkt, 0);
	WRITE_CHAR(wpkt, 0);
	//WRITE_LONG(wpkt, 0);
	WRITE_LONG(wpkt, GetID());
	Square l_shape{ {224700,224700}, 0 };
	this->SetPos(l_shape.centre);
	m_pPlayer->GetSession()->sendData(wpkt);
	pCMap->Enter(&l_shape, this);

	return true;
}

bool CCharacter::Cmd_BeginMove(short sPing, Point * pPoint, char chPointNum, char chStopState)
{
	CMoveAble::SMoveInit MoveInit;
	MoveInit.usPing = sPing;
	memcpy(MoveInit.SInflexionInfo.SList, pPoint, sizeof(Point) * chPointNum);
	MoveInit.SInflexionInfo.sNum = chPointNum;
	MoveInit.STargetInfo.chType = 0;
	MoveInit.sStopState = chStopState;
	m_CAction.Add(enumACTION_MOVE, &MoveInit);
	m_CAction.DoNext(0,0);
	return true;
}

void CCharacter::BeginAction(RPACKET & pk)
{
	uLong ulPacketId = READ_LONG(pk);
	m_ulPacketID = ulPacketId;
	char chActionType = READ_CHAR(pk);
	uShort usTurnNum = 0;
	cChar * pData = READ_SEQ(pk, usTurnNum);
	Point Path[32];
	char chPointNum = char(usTurnNum / sizeof(Point));
	DWORD m_dwPing = 100;

	memcpy(Path, pData, chPointNum * sizeof(Point));
	Cmd_BeginMove(m_dwPing,Path,chPointNum);
	//NotiChgToEyeshot(WPACKET(pk));

}
