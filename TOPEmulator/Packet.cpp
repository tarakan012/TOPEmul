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
WPacket & WPacket::operator=(const WPacket & wpkt)
{
	memcpy(const_cast<char*>(getDataAddr()), wpkt.getDataAddr(), wpkt.getDataLen());
	m_wpos = wpkt.m_wpos;
	return *this;
}
WPacket & WPacket::operator=(const RPacket & rpkt)
{
	m_wpos = rpkt.getDataLen()-em_cmdsize;
	memcpy(const_cast<char*>(getDataAddr()), rpkt.getDataAddr(), rpkt.getDataLen());
	return *this;
}
bool WPacket::writeCmd(uShort cmd)
{
	boost::endian::endian_reverse_inplace<uShort>(cmd);
	memcpy(const_cast<char*>(getDataAddr()), (char*)&cmd, sizeof(uShort));
	return true;
}
bool WPacket::writeChar(uChar ch)
{
	memcpy(const_cast<char*>(getDataAddr()) + getDataLen(), (cChar*)&ch, sizeof(uShort));
	m_wpos += sizeof(uShort);
	return true;
}
bool WPacket::writeShort(uShort sh)
{
	boost::endian::endian_reverse_inplace<uShort>(sh);
	memcpy(const_cast<char*>(getDataAddr())+getDataLen(), (cChar*)&sh, sizeof(uShort));
	m_wpos += sizeof(uShort);
	return true;
}
bool WPacket::writeLong(uLong lg)
{
	boost::endian::endian_reverse_inplace<uLong>(lg);
	memcpy(const_cast<char*>(getDataAddr()) + getDataLen(), (cChar*)&lg, sizeof(uLong));
	m_wpos += sizeof(uLong);
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
	memcpy(const_cast<char*>(getDataAddr())-sizeof(uint32_t), (char*)&ses, sizeof(uint32_t));
}
//--------------- RPacket ----------------
uShort RPacket::readCmd()
{
	uShort l_cmd;
	memcpy((char*)&l_cmd, const_cast<char*>(getDataAddr()), sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(l_cmd);
	return l_cmd;
}

RPacket::RPacket() : m_head(6)
{
	m_buffer = new char[64 * 1024];
	m_rpos = 0;
	m_len = 0;
	m_revpos = 0;
}

cChar * RPacket::readString(uShort len)
{
	uShort	l_retlen = 0;
	cChar * l_ret = readSequence(l_retlen);
	len = l_retlen - 1;
	return l_ret;
}

cChar * RPacket::readSequence(uShort & retlen)
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

uShort RPacket::reverseReadShot()
{
	uShort l_retval = 0;
	m_revpos += sizeof(uShort);
	std::cout << "m_revpos: " << m_revpos << std::endl;
	memcpy((char*)&l_retval, getDataAddr() + getDataLen() - m_revpos, sizeof(uShort));
	std::cout << "l_retval: " << l_retval << std::endl;

	boost::endian::endian_reverse_inplace<uShort>(l_retval);
	return l_retval;
}

void RPacket::readPktLen()
{
	memcpy((char*)&m_len, const_cast<char*>(getPktAddr()), sizeof(uShort));
	boost::endian::endian_reverse_inplace<uShort>(m_len);
}

RPacket::~RPacket()
{
	delete[] m_buffer;
}

RPacket & RPacket::operator=(const WPacket & wpkt)
{
	m_rpos = 0;
	m_revpos = 0;
	m_len = wpkt.getDataLen() + m_head;
	memcpy(const_cast<char*>(getDataAddr()), wpkt.getDataAddr(), wpkt.getDataLen());
	return *this;
}
