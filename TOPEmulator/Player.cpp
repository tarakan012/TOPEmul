#include "Player.h"

//CPlayer::~CPlayer()
//{
//}

short CPlayer::FindIndexByChaName(string chaname)
{
	for (short i = 0; i < m_chanum; i++)
	{
		if (m_chaname[i] == chaname)
		{
			return i;
		}
	}
	return -1;
}
