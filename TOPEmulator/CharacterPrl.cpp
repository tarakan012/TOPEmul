#include "Character.h"



enum{em_say_interval=1};

void CCharacter::ProcessPacket(uShort usCmd, RPACKET rpk)
{
	switch (usCmd)	
	{
	case CMD_CS_SAY :
	{
	DWORD dwNowTick = duration_cast<seconds>(steady_clock::now().time_since_epoch()).count();
	if (dwNowTick - m_dwLastSayTick < em_say_interval)
	{
		m_dwLastSayTick = dwNowTick;
		break;
	}
	uShort l_retlen = 0;
	cChar * l_content = READ_SEQ(rpk, l_retlen);
	m_dwLastSayTick = dwNowTick;
	WPACKET wpk;
	WRITE_CMD(wpk, CMD_SC_SAY);
	WRITE_LONG(wpk, m_ID);
	WRITE_SEQ(wpk, l_content, l_retlen);
	NotiChgToEyeshot(wpk);
	break;
	}
	default:
		break;
	}
}
