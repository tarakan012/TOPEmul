#include "EyeshotCell.h"
#include "Entity.h"
#include "Character.h"
#include <algorithm>

//#include "boost\foreach.hpp"

CEyeshotCell::CEyeshotCell()
{
	m_lChaCount = 0;
}

void CEyeshotCell::EnterEyeshot(CEntity * pCEnt)
{
	 CCharacter * pCha = pCEnt->IsCharacter();
	 for(long i =0;i<m_lChaCount;i++)
	 {
		 CCharacter * pCellCha = m_ChaList.at(i);
		 pCha->OnBeginSeen(pCellCha);
		 pCellCha->OnBeginSeen(pCha);
		// pCellCha->OnBeginSeen(pCha);	
	 }
}

void CEyeshotCell::AddEntity(CCharacter * pCCha)
{
	m_ChaList.push_back(pCCha);
	m_lChaCount ++;
}

void CEyeshotCell::DelEntity(CEntity * pCEnt)
{
	auto res = std::find(m_ChaList.begin(), m_ChaList.end(), pCEnt);
	if (res != m_ChaList.end())
	{
		m_ChaList.erase(res);
	}
	m_lChaCount --;
}
//--
void CEyeshotCell::OutEyeshot(CEntity * pCEnt)
{
	for (auto & pCellCha : m_ChaList)
	{
		if (pCellCha != pCEnt)
		{
			pCellCha->OnEndSeen(pCEnt->IsCharacter());
			pCEnt->OnEndSeen(pCEnt->IsCharacter());
		}
	}
	//m_ChaList.(pCEnt);
}
