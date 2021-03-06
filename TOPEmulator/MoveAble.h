#pragma once

#include<cstdlib>
#include "FightAble.h"
//class CEntity;
class CMoveAble : public CFightAble
{
public:
	struct STarget
	{
		struct {
			char chType;
			long lInfo1;
			long lInfo2;
		};
		long UlDist;
	};
	struct SPointList
	{
		Point SList[32];
		short sNum;
	};
	struct SMoveInit
	{
		SPointList SInflexionInfo;
		uShort usPing;
		STarget STargetInfo;
		short sStopState;
	};

	struct SMoveRedundance
	{
		uLong ulStartTime;
		uLong ulLeftTime;
	};
	struct SMoveProc
	{
		uLong ulElapse;//�������������� ������������ �������� (��)
		short sState;
		short sCurInflexion;
		SPointList sNoticePoint;
		char chRequestState;
	};
	CMoveAble();
	Square GetShape() { return m_shape;	}
	virtual void ReflectINFof(CMoveAble * pMoveAble, WPACKET & pk) {};
	virtual CMoveAble * IsMoveAble() { return this; }
	void DesireMoveBegin(SMoveInit * pSMoveInit);
	void BeginMove();
	void OnMove(uLong dwCurTime);
	void EndMove();
	void NotiMovToEyeshot();
	cChar AttemptMove(uLong ulPreMoveDist, bool bNotiInflexion);
	char LinearAttemtMove(Point STar, double distance, uLong * ulElapse);
	bool overlap(long & xdist, long & ydist);
private:
	SMoveInit m_SMoveInit;
	bool m_bOnMove;
	SMoveProc m_SMoveProc;
	uShort m_usHeartbeatFre;
	SMoveRedundance m_SMoveRedu;
	uLong m_ulHeartbeatTick;
	long m_attr_mspd;
};