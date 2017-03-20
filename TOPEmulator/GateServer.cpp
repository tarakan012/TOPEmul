#include "stdafx.h"
#include "GateServer.h"


GateServer::GateServer() : TCPServer(3)
{
	start_server();
}

void GateServer::onConnected()
{
	WPacket lpkt;
	lpkt.writeCmd(CMD_SC_CHAPSTR);
	std::string lstr_time = dataTimeToString(now(), "[%m-%d %H:%M:%S:100]"); // milisecond?
	lpkt.writeSESS(128);
	lpkt.writeString(lstr_time.c_str());
	lpkt.writePktLen();
	sendData(lpkt);
}

void GateServer::onProccesData(RPacket & rpkt)
{
	uShort l_cmd = 0;
	l_cmd = rpkt.readCmd();
}
