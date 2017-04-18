#include "stdafx.h"
#include "LogHundler.h"

CLogHandler * CLogHandler::m_pCLogHundler = nullptr;
IP7_Trace * CLogHandler::m_pTrace = nullptr;

CLogHandler::CLogHandler(void) 
	: m_pClient(NULL)
{

}

CLogHandler::~CLogHandler(void)
{

}

bool CLogHandler::Init()
{
	m_pClient = P7_Create_Client(TM("/ P7.Sink = Baical / P7.Addr = 127.0.0.1"));
	if (m_pClient == NULL)
	{
		cout << "Error IP7_Client" << endl;
		return false;
	}
	m_pTrace = P7_Create_Trace(m_pClient, TM("Test"));
	return true;
}

IP7_Trace & CLogHandler::GetTrace()
{
	return *m_pTrace;
}

bool CLogHandler::Release()
{
	m_pClient->Release();
	return true;
}

CLogHandler & CLogHandler::GetInstance()
{
	if (m_pCLogHundler == NULL)
	{
		m_pCLogHundler = new CLogHandler;
	}
	return *m_pCLogHundler;
}
