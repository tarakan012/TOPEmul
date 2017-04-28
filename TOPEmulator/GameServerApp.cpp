#include "GameServerApp.h"
#include "Character.h"
#include "Player.h"
#include "TCPSession.h"

bool GameServerApp::SendToClient(WPACKET wpk, std::vector<CCharacter*> ChaList)
{
	for (auto & elem : ChaList)
	{
		elem->GetPlayer()->GetSession()->sendData(wpk);
	}
	return false;
}


