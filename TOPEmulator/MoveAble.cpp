#include "MoveAble.h"
#include "Character.h"
#include "SubMap.h"

CMoveAble::CMoveAble()
{
	 m_attr_mspd = 700; // --

	m_usHeartbeatFre = 0;
	m_SMoveInit.STargetInfo.chType = 0;
	m_SMoveProc.sState = enumMSTATE_ARRIVE;
	m_SMoveProc.chRequestState = 0;
	m_ulHeartbeatTick = 0;
	m_bOnMove = false;
	//m_shape.centre = Point{ 224700, 270400 };
}

void CMoveAble::DesireMoveBegin(SMoveInit * pSMoveInit)
{
	memcpy(&m_SMoveInit, pSMoveInit, sizeof(SMoveInit));
	BeginMove();
}

void CMoveAble::BeginMove()
{
	if (false)
	{
		for (size_t i = m_SMoveInit.SInflexionInfo.sNum; i > 0; --i)
		{
			m_SMoveInit.SInflexionInfo.SList[i] = m_SMoveInit.SInflexionInfo.SList[i - 1];
		}
		m_SMoveInit.SInflexionInfo.SList[0];//--
		m_SMoveInit.SInflexionInfo.sNum += 1;
	}

	SetPos(m_SMoveInit.SInflexionInfo.SList[0]);//--
	m_SMoveProc.sCurInflexion = 1;
	if (m_SMoveProc.chRequestState == 1)
	{

	}
	else
	{
		m_SMoveProc.sState = enumMSTATE_ON;
	}
	m_ulHeartbeatTick = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
	m_usHeartbeatFre = 300;
	m_SMoveRedu.ulLeftTime = m_usHeartbeatFre + m_SMoveInit.usPing;
	uLong ulAttemtDist = m_SMoveRedu.ulLeftTime * m_attr_mspd / 1000;
	m_SMoveProc.sState |= AttemptMove(ulAttemtDist, false);
	if (m_SMoveProc.ulElapse > 0)
	{
		NotiMovToEyeshot();
		if (m_SMoveProc.sState != enumMSTATE_ON)
		{

		}
		else
		{
			m_bOnMove = true;
		}
	}
	/*m_SMoveProc.sNoticePoint.sNum = m_SMoveInit.SInflexionInfo.sNum;
	memcpy(&m_SMoveProc.sNoticePoint.SList,&m_SMoveInit.SInflexionInfo.SList, m_SMoveInit.SInflexionInfo.sNum * sizeof(Point));
	m_pCSubMap->MoveTo(this, m_SMoveInit.SInflexionInfo.SList[1]);*/
	//NotiMovToEyeshot();
}

void CMoveAble::OnMove(uLong dwCurTime)
{
	if (!m_bOnMove) return;
	uLong ulCurTick = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
	uLong ulWillElapce = ulCurTick - m_ulHeartbeatTick;
	uLong ulAttemptDist = 0;
	m_ulHeartbeatTick = ulCurTick;
	bool bAttemtMove = false;
	if (m_SMoveProc.sState == enumMSTATE_ON)
	{
		ulAttemptDist = ulWillElapce * m_attr_mspd / 1000;
		if (ulAttemptDist > 0)
		{
			m_SMoveProc.sState = AttemptMove(ulAttemptDist,false);
			bAttemtMove = true;
		}

	}
	if (bAttemtMove)
	{
		NotiMovToEyeshot();
	}
	if (m_SMoveProc.sState != enumMSTATE_ON)
	{
		m_bOnMove = false;
	}
	if (bAttemtMove)//--
	{

	}
}

void CMoveAble::EndMove()
{
	m_SMoveProc.chRequestState = 1;

}

void CMoveAble::NotiMovToEyeshot()
{
	WPACKET pk;
	WRITE_CMD(pk, CMD_SC_NOTIACTION);
	WRITE_LONG(pk, m_ID);
	WRITE_LONG(pk, m_ulPacketID);
	WRITE_CHAR(pk, enumACTION_MOVE);
	WRITE_SHORT(pk,1);//m_SMoveProc.sState
	if (m_SMoveProc.sState != enumMSTATE_ON)//
	{
		WRITE_SHORT(pk, m_SMoveInit.sStopState);
	}
	WRITE_SEQ(pk, (cChar *)m_SMoveProc.sNoticePoint.SList, m_SMoveProc.sNoticePoint.sNum * sizeof(Point));
	NotiChgToEyeshot(pk);
//	ReflectINFof(this, pk);
}

cChar CMoveAble::AttemptMove(uLong ulPreMoveDist, bool bNotiInflexion)
{
	double dLeftDist = ulPreMoveDist;
	char chRet = 0;//state_on
	uLong ulElapce = 0;
	Point SAttemtTar, SSrc;
	char chAttemtMove;
	double dCurStep;
	const short csStep = 150;
	Point SPos, SBeforePos;
	SAttemtTar = m_SMoveInit.SInflexionInfo.SList[m_SMoveProc.sCurInflexion];
	SBeforePos = SSrc = GetShape().centre;
	m_SMoveProc.sNoticePoint.sNum = 0;
	m_SMoveProc.sNoticePoint.SList[m_SMoveProc.sNoticePoint.sNum++] = SSrc;
	m_SMoveProc.ulElapse = 0;
	dCurStep = dLeftDist;
	Square SReqShape = { { 0,0 },0 };
	long lReqDist = 0;
	long lMoveDist = 0;
	long lDistX2, lDistY2;
	long lPreMoveDist = 0;
	lPreMoveDist = ulPreMoveDist;
	while (true)
	{
		if (dCurStep > dLeftDist)
		{
			dCurStep = dLeftDist;
		}
		chAttemtMove = LinearAttemtMove(SAttemtTar, dCurStep, &ulElapce);
		m_SMoveProc.ulElapse += ulElapce; // 9128
		lDistX2 = (SSrc.x - GetPos().x)*(SSrc.x - GetPos().x);
		lDistY2 = (SSrc.y - GetPos().y)*(SSrc.y - GetPos().y);
		lMoveDist += std::sqrt(lDistY2 + lDistX2);
		SPos = GetShape().centre;
		if (chAttemtMove == -1)
		{
			m_SMoveProc.sCurInflexion++;
			if (m_SMoveProc.sCurInflexion < m_SMoveInit.SInflexionInfo.sNum)
			{
				SAttemtTar = m_SMoveInit.SInflexionInfo.SList[m_SMoveProc.sCurInflexion];
				if (bNotiInflexion || lMoveDist >= lPreMoveDist)

					if (ulElapce > 0)
					{
						m_SMoveProc.sNoticePoint.SList[m_SMoveProc.sNoticePoint.sNum++]
							= m_SMoveInit.SInflexionInfo.SList[m_SMoveProc.sCurInflexion - 1];
					}
			}
			else
			{
				chRet |= enumMSTATE_ARRIVE;
				break;
			}
		}

		dLeftDist -= sqrt((SSrc.x - SPos.x)*(SSrc.x - SPos.x) +
			(SSrc.y - SPos.y) * (SSrc.y - SPos.y));
		if (dLeftDist < 1)
		{
			break;
		}
		SSrc = SPos;
	}
	SPos = GetShape().centre;
	if (ulElapce>0)
	{
		m_SMoveProc.sNoticePoint.SList[m_SMoveProc.sNoticePoint.sNum++]
			= SPos;
	}
	m_shape.centre = SBeforePos;
	//m_pCSubMap->MoveTo(this, SPos);
	return chRet;
}

char CMoveAble::LinearAttemtMove(Point STar, double distance, uLong *ulElapse)
{
	uLong ulMoveSpeed = 1500;
	char l_retval = 1;
	long l_elapse = distance * 1000 / ulMoveSpeed;
	double l_dist2 = distance*distance;
	const Point l_src = GetShape().centre;
	const long lc_xdist = STar.x - l_src.x;
	const long lc_ydist = STar.y - l_src.y;
	long l_xdist = lc_xdist;
	long l_ydist = lc_ydist;
	double l_xdist2 = l_xdist*l_xdist;
	double l_ydist2 = l_ydist*l_ydist;
	double l_xydist2 = l_xdist2 + l_ydist2;
	bool l_arraim;
	if ((l_dist2 > l_xydist2) || (std::abs(l_dist2 - l_xydist2) < 0.0001))
	{
		l_arraim = true;
	}
	else
	{
		l_arraim = false;
	}
	if (l_arraim) {
		if (l_xdist || l_ydist)
		{
			double l_tmp = l_xydist2 * 1000 * 1000;
			l_tmp /= ulMoveSpeed;
			l_elapse = sqrt(l_tmp);
		}
		else
		{
			l_elapse = 0;
		}
		l_retval = -1;
	}
	bool bIs45Dir = std::abs(lc_xdist) == std::abs(lc_ydist) ? true : false;
	char chDirX = l_xdist < 0 ? -1 : 1;
	char chDirY = l_ydist < 0 ? -1 : 1;
	if (!l_arraim)
	{
		l_xdist = std::sqrt(l_dist2*l_xdist2) / l_xydist2*chDirX;
		l_ydist = std::sqrt(l_dist2*l_ydist2) / l_xydist2*chDirY;
	}
	if (bIs45Dir)
	{
		if ((l_src.x + l_xdist) % 10 == 0)//--
		{
			l_xdist -= chDirX;
		}
		l_ydist = std::abs(l_xdist)*chDirY;
	}
	if (l_elapse>0)
	{
		bool l_lap = overlap(l_xdist, l_ydist);
		m_shape.centre.x = l_src.x + l_xdist;
		m_shape.centre.y = l_src.y + l_ydist;
		if (l_lap)
		{
			//--
		}
	}
	*ulElapse = l_elapse;
	return l_retval;
}

bool CMoveAble::overlap(long &xdist, long &ydist)//--
{
	bool b_retval = false;
	return b_retval;
}