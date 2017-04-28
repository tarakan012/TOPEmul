#pragma once

class GameServerApp
{
public:
	static bool SendToClient(WPACKET wpk, std::vector<CCharacter *> ChaList);
};