#pragma once

#include "MoveAble.h"
#include "Entity.h"
class CAction
{
	struct SActionQueue
	{
		short sType;
		void * pInit;
	};
public:
	CAction(CEntity * pCEntity);
	void Add(short sActionType, void * pActionData);
	bool DoNext(short sActionType, short sActionState);
private:
	SActionQueue m_SAction[2];
	short m_sActionNum;
	short m_sCurAction;
		
	CMoveAble::SMoveInit m_SMoveInit;
	CEntity * m_pCEntity;
};