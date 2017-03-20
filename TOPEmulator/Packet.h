#pragma once
#include "stdafx.h"


enum { em_cmdsize = sizeof(uShort) };

class WPacket
{
public:
	WPacket();
	bool writeCmd(uShort cmd);
	bool writeString(cChar * str);
	bool writeSequence(cChar * seq, uShort len);
	bool writeShort(uShort sh);
	void writePktLen() const;
	uShort getPktLen()const { return m_head + em_cmdsize + m_wpos; }
	cChar * getPktAddr()const { return m_buffer; }

	~WPacket();
	void writeSESS(uint32_t ses) const;
	cChar * getDataAddr() const
	{
		return m_buffer + m_head;
	}
	uShort getDataLen() const
	{
		return em_cmdsize + m_wpos;
	}
private:
	char * m_buffer;
	uShort const m_head;
	uShort m_wpos;
};

class RPacket
{
public:
	RPacket();
	cChar *	readString(uShort *len = 0);
	cChar *	readSequence(uShort &retlen);
	uShort readCmd();
	uShort readShort();
	void writePktLen() const;
	uShort getPktLen()const { return m_head + em_cmdsize + m_rpos; }
	cChar * getPktAddr()const { return m_buffer; }
	~RPacket();
	void writeSESS(uint32_t ses) const;
	cChar * getDataAddr() const
	{
		return m_buffer + m_head;
	}
	uShort getDataLen() const
	{
		return em_cmdsize + m_rpos;
	}
private:
	char * m_buffer;
	uShort const m_head;
	uShort m_rpos;
};

