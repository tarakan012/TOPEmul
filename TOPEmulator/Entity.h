#pragma once

class CSubMap;
class CEntity
{
	friend class CMoveAble;
	friend class CCharacter;
public:
//	CEntity(){}	
	virtual CMoveAble * IsMoveAble() { return 0; }
	virtual CCharacter * IsCharacter() { return 0; }
	void EndSee(CEntity * pCEnt) { OnEndSeen(pCEnt); }
	virtual void OnEndSeen(CEntity * pCEnt) {}
	Point GetPos() { return m_shape.centre; }
	void SetPos(Point SPos) { m_shape.centre = SPos; }

	void SetSubMap(CSubMap * pSubMap) { m_pCSubMap = pSubMap; }
	CSubMap * GetSubMap(void)const { return m_pCSubMap; }
	void NotiChgToEyeshot(WPACKET & pk);
	long GetID() { return m_ID; }
	void SetID(long id) { m_ID = id; }
	void SetName(std::string strName) { m_name = strName; }
	std::string GetName() const { return m_name; }
	long m_ID;
private:
	CSubMap * m_pCSubMap;
	Square m_shape;
	std::string  m_name;

};
