#pragma once

#include<vector>

class CEntity;
class CCharacter;
class CEyeshotCell
{
public:
	void EnterEyeshot(CEntity * pCEnt);
	void AddEntity(CCharacter * pCCha);
private:
	std::vector<CCharacter *> m_VecCha;

};

