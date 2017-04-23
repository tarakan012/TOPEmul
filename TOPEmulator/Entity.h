#pragma once

class CEntity
{
	friend class CMoveAble;
	friend class CCharacter;
public:
//	CEntity(){}	
	virtual CMoveAble * IsMoveAble() { return 0; }
	virtual CCharacter * IsCharacter() { return 0; }
};
