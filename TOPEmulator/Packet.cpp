#include "stdafx.h"
#include "Packet.h"


//WPacket
WPacket::WPacket() : m_head(6)
{
	m_buffer = new char[64 * 1024];
	m_wpos = 0;
}
bool WPacket::writeCmd(uShort cmd)
{
	boost::endian::endian_reverse_inplace<uShort>(cmd);
	memcpy(const_cast<char*>(getDataAddr()), (char*)&cmd, sizeof(uShort));
	return true;
}
bool WPacket::writeString(cChar * str)
{
	return writeSequence(str, strlen(str) + 1);
}
bool WPacket::writeSequence(cChar * seq, uShort len)
{
	if (!writeShort(len))	return false;
	memcpy(const_cast<char*>(getDataAddr()) + getDataLen(), seq, len);
	m_wpos += len;
	return true;
}
bool WPacket::writeShort(uShort sh)
{
	boost::endian::endian_reverse_inplace<uShort>(sh);
	memcpy(const_cast<char*>(getDataAddr())+getDataLen(), (char*)&sh, sizeof(uShort));
	m_wpos += sizeof(uShort);
	return true;
}
void WPacket::writePktLen()const
{
	uShort l_len = getPktLen();
	boost::endian::endian_reverse_inplace<uShort>(l_len);
	memcpy(const_cast<char*>(getPktAddr()), (char*)&l_len, sizeof(uShort));
}
WPacket::~WPacket()
{
	delete[] m_buffer;
}
void WPacket::writeSESS(uint32_t ses)const
{
	boost::endian::endian_reverse_inplace<uint32_t>(ses);
	memcpy(const_cast<char*>(getDataAddr())-sizeof(uint32_t), (char*)&ses, sizeof(uint32_t));
}
// RPacket
uShort RPacket::readCmd()
{
	uShort l_cmd;
	memcpy((char*)&l_cmd, const_cast<char*>(getDataAddr()), sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(l_cmd);
	return l_cmd;
}

RPacket::RPacket() : m_head(0)
{
	m_buffer = new char[64 * 1024];
	m_rpos = 0;
}

cChar * RPacket::readString(uShort * len)
{
	uShort	l_retlen;
	cChar * l_ret = readSequence(l_retlen);
	*len = l_retlen - 1;
	return l_ret;
}

cChar * RPacket::readSequence(uShort & retlen)
{
	cChar * l_retseq = 0;
	retlen = readShort();
	l_retseq = getDataAddr() + getDataLen();
	m_rpos += retlen;
	return l_retseq;
}
uShort RPacket::readShort()
{
	uShort l_retval = 0;
	memcpy((char*)l_retval, const_cast<char*>(getDataAddr()) + getDataLen(), sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(l_retval);
	m_rpos += sizeof(uShort);
	return l_retval;
}

RPacket::~RPacket()
{
	delete[] m_buffer;
}
