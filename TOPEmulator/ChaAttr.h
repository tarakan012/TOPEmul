#pragma once

#define ATTR_MAX_NUM 213

class CChaAttr
{
	short GetChangeNumClient() {return m_sChangeNumClient;}
private:
	DWORD64 m_lAttribute[ATTR_MAX_NUM];
	short m_sChangeNumClient = 0;
};