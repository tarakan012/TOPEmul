#pragma once

#define WPACKET WPacket
#define RPACKET RPacket

#define WRITE_CMD(pkt, cmd) pkt.WriteCmd(cmd)
#define WRITE_CHAR(pkt, c) pkt.WriteChar(c)
#define WRITE_SHORT(pkt, s) pkt.WriteShort(s)
#define WRITE_LONG(pkt, l) pkt.WriteLong(l)
#define WRITE_SEQ(pkt, seq, len) pkt.WriteSequence(seq, len)
#define WRITE_STRING(pkt, str) pkt.WriteString(str)
#define READ_CMD(pkt) pkt.ReadCmd()
#define READ_CHAR(pkt) pkt.ReadChar()
#define READ_SHORT(pkt) pkt.ReadShort()
#define READ_LONG(pkt) pkt.ReadLong()
#define READ_SEQ(pkt, len) pkt.ReadSequence(len)
#define READ_STRING(pkt) pkt.ReadString()

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
	bool WriteCmd(uShort cmd);
	bool WriteChar(uChar ch);
	bool WriteString(cChar * str);
	bool WriteSequence(cChar * seq, uShort len);
	bool WriteShort(uShort sh);
	bool WriteLong(uLong lg);
	void WritePktLen() const;
	uShort getPktLen()const { return m_head + em_cmdsize + m_wpos; }
	cChar * getPktAddr()const { return m_buffer; }

	~WPacket();
	void WriteSESS(uint32_t ses) const;
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
	RPacket(const WPacket& wpkt);
	~RPacket();
	RPacket& operator=(const WPacket& wpkt);
	cChar *	readString(uShort len = 0);
	cChar *	readSequence(uShort &retlen);
	uShort readCmd();
	uShort hasData()const { return (m_len > (m_head + em_cmdsize)) ? (m_len - m_head - em_cmdsize): 0; }
	uShort readShort();
	uShort reverseReadShot();
	void readPktLen();
	void WritePktLen(uShort len);
	uShort getPktLen()const { return m_len; }
	cChar * getPktAddr()const { return m_buffer; }
	void setPktLen(uShort len) { m_len = len; }
	void WriteSESS(uint32_t ses) const;
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

