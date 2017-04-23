#include "Action.h"
#include "Character.h"

CAction::CAction(CEntity * pCEntity)
{
	m_pCEntity = pCEntity;
	m_sActionNum = 0;
	m_sCurAction = -1;
}
void CAction::Add(short sActionType, void * pActionData)
{
	m_SAction[m_sActionNum].sType = sActionType;
	memcpy(&m_SMoveInit, pActionData, sizeof(m_SMoveInit));
	m_SAction[m_sActionNum].pInit = &m_SMoveInit;
	m_sActionNum++;
}
bool CAction::DoNext(short sActionType, short sActionState)
{
	switch (m_SAction[m_sCurAction + 1].sType)
	{
	case enumACTION_MOVE:
	{
		m_sCurAction++;
		CMoveAble * pCmoveAble = m_pCEntity->IsMoveAble();
		pCmoveAble->DesireMoveBegin((CMoveAble::SMoveInit*)m_SAction[m_sCurAction].pInit);
		m_sActionNum = 0;
		m_sCurAction = -1;
		break;
	}
	default:
		break;
	}
	return true;
}
