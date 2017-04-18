#pragma once

class CItemAttr
{
public:
	CItemAttr() { m_bInitFlug = false; }
private:
	short m_Attr[58];
	bool m_bInitFlug;

};