#include "EyeshotCell.h"
//#include "Entity.h"
#include "Character.h"
//#include "boost\foreach.hpp"

void CEyeshotCell::EnterEyeshot(CEntity * pCEnt)
{
	 CCharacter * pCha = pCEnt->IsCharacter();
	 for(long i =0;i<m_lChaCount;i++)
	 {
		 CCharacter * pCellCha = m_VecCha.at(i);
		 pCha->OnBeginSeen(pCellCha);
		// pCellCha->OnBeginSeen(pCha);	
	 }
}

void CEyeshotCell::AddEntity(CCharacter * pCCha)
{
	m_VecCha.push_back(pCCha);
	m_lChaCount ++;
}