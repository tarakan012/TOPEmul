#include "EyeshotCell.h"
//#include "Entity.h"
#include "Character.h"
#include "boost\foreach.hpp"

void CEyeshotCell::EnterEyeshot(CEntity * pCEnt)
{
	 CCharacter * pCha = pCEnt->IsCharacter();
	 BOOST_FOREACH(CCharacter * pCellCha, m_VecCha)
	 {
		 pCha->OnBeginSeen(pCellCha);
		 pCellCha->OnBeginSeen(pCha);	
	 }
}

void CEyeshotCell::AddEntity(CCharacter * pCCha)
{
	m_VecCha.push_back(pCCha);
}