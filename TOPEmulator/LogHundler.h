#pragma once

#include "P7_Client.h"
#include "P7_Trace.h"

#define LOG_INFO(istring, iformat) CLogHandler::GetTrace().P7_INFO(0,TM(istring),iformat);

class CLogHandler
{	
public:
	~CLogHandler(void);
	bool Init();
	bool Release();
	static IP7_Trace & GetTrace();
	static CLogHandler & GetInstance();
private:
	CLogHandler(void);
	static CLogHandler * m_pCLogHundler;
	static IP7_Trace * m_pTrace;
	IP7_Client * m_pClient;
};