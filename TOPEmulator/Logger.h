#pragma once

#include "P7_Client.h"
#include "P7_Trace.h"

#define LOG_INFO(istring, iformat) CLogger::GetTrace().P7_INFO(0,TM(istring),iformat);

class CLogger
{	
public:
	~CLogger(void);
	bool Init();
	bool Release();
	static IP7_Trace & GetTrace();
	static CLogger & GetInstance();
private:
	CLogger(void);
	static CLogger * m_pCLogHundler;
	static IP7_Trace * m_pTrace;
	IP7_Client * m_pClient;
};