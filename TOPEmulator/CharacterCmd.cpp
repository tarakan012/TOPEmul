#include "Character.h"
#include "SubMap.h"
#include "MapRes.h"
#include "GameApp.h"

CCharacter::CCharacter()
	: m_CAction(this)
{

}
bool CCharacter::Cmd_EnterMap(WPACKET & wpkt)
{
	CSubMap * pCMap = 0;
	CMapRes * pCMapRes = 0;

	pCMapRes = g_pCGameApp->FindMapByName("garner");
	pCMap = pCMapRes->GetCopy();
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
	WRITE_LONG(wpkt, 123);
	Square l_shape{ {224700,224700}, 0 };
	//pCMap->Enter(&l_shape, this);

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

}
