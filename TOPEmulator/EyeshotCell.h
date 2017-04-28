#pragma once

#include<vector>

class CEntity;
class CCharacter;
class CEyeshotCell
{
public:
	CEyeshotCell();
	void EnterEyeshot(CEntity * pCEnt);
	void AddEntity(CCharacter * pCCha);
	void DelEntity(CEntity * pCEnt);
	void OutEyeshot(CEntity * pCEnt);
	std::vector<CCharacter *> m_ChaList;
	long m_lChaCount;
private:

};

