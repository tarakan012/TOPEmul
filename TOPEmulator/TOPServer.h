#pragma once

#include "TCPServer.h"
//#include "TCPSession.h"
#include "Singleton.h"

class TCPServer;
class TOPServer : public TCPServer, public	CSingleton<TOPServer>
{
public:
	//friend class CSingleton<TOPServer>;
	//SINGELTON_FREND_CLASS_REGISTER(TOPServer);
	TOPServer();
	bool Init();
	TOPServer & GetInstance();
};
