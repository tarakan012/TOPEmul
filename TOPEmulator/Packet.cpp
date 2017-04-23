#include "Packet.h"

//WPacket
WPacket::WPacket() : m_head(6)
{
	m_buffer = new char[64 * 1024];
	m_wpos = 0;
}
WPacket::WPacket(const WPacket & wpkt) : m_head(6)
{
	m_buffer = new char[64 * 1024];
	m_wpos = wpkt.m_wpos;
	memcpy(const_cast<char*>(getDataAddr()), wpkt.getDataAddr(), wpkt.getDataLen());
}
WPacket::WPacket(WPacket && wpkt) : m_head(6)
{
	m_buffer = wpkt.m_buffer;
	wpkt.m_buffer = nullptr;
	m_wpos = wpkt.m_wpos;
}
WPacket & WPacket::operator=(const WPacket & wpkt)
{
	memcpy(const_cast<char*>(getDataAddr()), wpkt.getDataAddr(), wpkt.getDataLen());
	m_wpos = wpkt.m_wpos;
	return *this;
}
WPacket & WPacket::operator=(WPacket && wpkt)
{
	delete [] m_buffer;
	m_buffer = wpkt.m_buffer;
	wpkt.m_buffer = nullptr;
	m_wpos = wpkt.m_wpos;
	return *this;
}
WPacket & WPacket::operator=(const RPacket & rpkt)
{
	m_wpos = rpkt.getDataLen()-em_cmdsize;
	memcpy(const_cast<char*>(getDataAddr()), rpkt.getDataAddr(), rpkt.getDataLen());
	return *this;
}
bool WPacket::WriteCmd(uShort cmd)
{
	boost::endian::endian_reverse_inplace<uShort>(cmd);
	memcpy(const_cast<char*>(getDataAddr()), (char*)&cmd, sizeof(uShort));
	return true;
}
bool WPacket::WriteChar(uChar ch)
{
	memcpy(const_cast<char*>(getDataAddr()) + getDataLen(), (cChar*)&ch, sizeof(uChar));
	m_wpos += sizeof(uChar);
	return true;
}
bool WPacket::WriteShort(uShort sh)
{
	boost::endian::endian_reverse_inplace<uShort>(sh);
	memcpy(const_cast<char*>(getDataAddr())+getDataLen(), (cChar*)&sh, sizeof(uShort));
	m_wpos += sizeof(uShort);
	return true;
}
bool WPacket::WriteLong(uLong lg)
{
	boost::endian::endian_reverse_inplace<uLong>(lg);
	memcpy(const_cast<char*>(getDataAddr()) + getDataLen(), (cChar*)&lg, sizeof(uLong));
	m_wpos += sizeof(uLong);
	return true;
}
bool WPacket::WriteString(cChar * str)
{
	return WriteSequence(str, strlen(str) + 1);
}
bool WPacket::WriteSequence(cChar * seq, uShort len)
{
	if (!WriteShort(len))	return false;
	memcpy(const_cast<char*>(getDataAddr()) + getDataLen(), seq, len);
	m_wpos += len;
	return true;
}
void WPacket::WritePktLen()const
{
	uShort l_len = getPktLen();
	boost::endian::endian_reverse_inplace<uShort>(l_len);
	memcpy(const_cast<char*>(getPktAddr()), (char*)&l_len, sizeof(uShort));
}
WPacket::~WPacket()
{
	delete[] m_buffer;
}
void WPacket::WriteSESS(uint32_t ses)const
{
	memcpy(const_cast<char*>(getDataAddr())-sizeof(uint32_t), (char*)&ses, sizeof(uint32_t));
}
//--------------- RPacket ----------------

RPacket::RPacket() : m_head(6)
{
	m_buffer = new char[64 * 1024];
	m_rpos = 0;
	m_len = 0;
	m_revpos = 0;
}

RPacket & RPacket::operator=(const WPacket & wpkt)
{
	m_rpos = 0;
	m_revpos = 0;
	m_len = wpkt.getDataLen() + m_head;
	memcpy(const_cast<char*>(getDataAddr()), wpkt.getDataAddr(), wpkt.getDataLen());
	return *this;
}

RPacket::RPacket(const WPacket & wpkt) : m_head(6)
{
	m_buffer = new char[64 * 1024];
	m_rpos = 0;
	m_revpos = 0;
	m_len = wpkt.getDataLen() + m_head;
	memcpy(const_cast<char*>(getDataAddr()), wpkt.getDataAddr(), wpkt.getDataLen());
}

uShort RPacket::readCmd()
{
	uShort l_cmd;
	memcpy((char*)&l_cmd, const_cast<char*>(getDataAddr()), sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(l_cmd);
	return l_cmd;
}
cChar * RPacket::ReadString(uShort len)
{
	uShort	l_retlen = 0;
	cChar * l_ret = ReadSequence(l_retlen);
	len = l_retlen - 1;
	return l_ret;
}

cChar * RPacket::ReadSequence(uShort & retlen)
{
	cChar * l_retseq = 0;
	retlen = readShort();
	l_retseq = getDataAddr() + em_cmdsize + m_rpos;
	m_rpos += retlen;
	return l_retseq;
}
uShort RPacket::readShort()
{
	uShort l_retval = 0;
	memcpy((char*)&l_retval, getDataAddr() + em_cmdsize + m_rpos, sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(l_retval);
	m_rpos += sizeof(uShort);
	return l_retval;
}

uLong RPacket::ReadLong()
{
	uLong l_retval = 0;
	memcpy((char*)&l_retval, getDataAddr() + em_cmdsize + m_rpos, sizeof(uLong));
	boost::endian::endian_reverse_inplace<uLong>(l_retval);
	m_rpos += sizeof(uLong);
	return l_retval;
}

uChar RPacket::ReadChar()
{
	uLong l_retval = 0;
	memcpy((char*)&l_retval, getDataAddr() + em_cmdsize + m_rpos, sizeof(uChar));
	m_rpos += sizeof(uChar);
	return l_retval;
}



uShort RPacket::reverseReadShot()
{
	uShort l_retval = 0;
	m_revpos += sizeof(uShort);
	memcpy((char*)&l_retval, getDataAddr() + getDataLen() - m_revpos, sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(l_retval);
	return l_retval;
}

void RPacket::readPktLen()
{
	memcpy((char*)&m_len, const_cast<char*>(getPktAddr()), sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(m_len);
}

void RPacket::WritePktLen(uShort len)
{
	boost::endian::endian_reverse_inplace<uShort>(len);
	memcpy(m_buffer, (char*)&len, sizeof(uShort));
}

RPacket::~RPacket()
{
	delete[] m_buffer;
}

