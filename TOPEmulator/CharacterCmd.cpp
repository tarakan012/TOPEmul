#include "Character.h"

bool CCharacter::Cmd_EnterMap(WPACKET & wpkt)
{
	//WPACKET wpkt;
	WRITE_CMD(wpkt, CMD_SC_ENTERMAP);
	WRITE_SHORT(wpkt, ERR_SUCCESS);
	WRITE_CHAR(wpkt, 0);//autolook
	WRITE_CHAR(wpkt, 0);//look
	WRITE_CHAR(wpkt, 1);//newcha
	WRITE_STRING(wpkt,"GARNER");
	WRITE_CHAR(wpkt, 1);//can team
	WriteBaseInfo(wpkt);
	WriteSkillbag(wpkt, 0);
	WriteAttr(wpkt,0);
	CKitbag l_kitbag;
	WriteKitbug(&l_kitbag,wpkt, 0);
	WriteShortcut(wpkt);
	WRITE_LONG(wpkt, 0);
	WRITE_CHAR(wpkt, 0);
	WRITE_LONG(wpkt, 0);
	WRITE_LONG(wpkt, 0);


	return true;
}