#pragma once
#include "stdafx.h"
#include "TCPServer.h"
//#include "TCPSession.h"
#include "DataTimeToString.h"
#include "Packet.h"

class GateServer : public TCPServer
{
public:
	GateServer();
	virtual void onConnected()final;
	virtual void onProccesData(RPacket & rpkt)final;

	//~GateServer();

private:

};


