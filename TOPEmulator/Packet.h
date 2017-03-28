#pragma once


enum { em_cmdsize = sizeof(uShort) };

class RPacket;

class WPacket
{
public:
	WPacket();
	WPacket(const WPacket &wpkt);
		
	WPacket(const RPacket &rpk);
	WPacket & operator=(const WPacket & wpkt);
	WPacket & operator=(const RPacket & rpkt);
	bool writeCmd(uShort cmd);
	bool writeString(cChar * str);
	bool writeSequence(cChar * seq, uShort len);
	bool writeShort(uShort sh);
	void writePktLen() const;
	uShort getPktLen()const { return m_head + em_cmdsize + m_wpos; }
	cChar * getPktAddr()const { return m_buffer; }

	~WPacket();
	void writeSESS(uint32_t ses) const;
	//m_buffer + m_head
	cChar * getDataAddr() const
	{
		return m_buffer + m_head;
	}
	//em_cmdsize + m_wpos
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
	~RPacket();
	RPacket& operator=(const WPacket& wpkt);
	cChar *	readString(uShort len = 0);
	cChar *	readSequence(uShort &retlen);
	uShort readCmd();
	uShort hasData()const { return (m_len > (m_head + em_cmdsize)) ? (m_len - m_head - em_cmdsize): 0; }
	uShort readShort();
	uShort reverseReadShot();
	void readPktLen();
	uShort getPktLen()const { return m_len; }
	cChar * getPktAddr()const { return m_buffer; }
	void setPktLen(uShort len) { m_len = len; }
	void writeSESS(uint32_t ses) const;
	cChar * getDataAddr() const
	{
		return m_buffer + m_head;
	}
	uShort getDataLen() const
	{
		return m_len - m_head;
	}
private:
	char * m_buffer;
	uShort const m_head;
	uShort m_rpos, m_len, m_revpos;
};

