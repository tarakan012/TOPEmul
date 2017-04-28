#include "Logger.h"

CLogger * CLogger::m_pCLogHundler = nullptr;
IP7_Trace * CLogger::m_pTrace = nullptr;

CLogger::CLogger(void) 
	: m_pClient(NULL)
{

}

CLogger::~CLogger(void)
{

}

bool CLogger::Init()
{
	m_pClient = P7_Create_Client(TM("/P7.Sink = FileTxt /P7.Format=\"{%cn} [%tf] %lv %ms\""));
	if (m_pClient == NULL)
	{
		cout << "Error IP7_Client" << endl;
		return false;
	}
	m_pTrace = P7_Create_Trace(m_pClient, TM("Test"));
	return true;
}

IP7_Trace & CLogger::GetTrace()
{
	return *m_pTrace;
}

bool CLogger::Release()
{
	m_pClient->Release();
	return true;
}

CLogger & CLogger::GetInstance()
{
	if (m_pCLogHundler == NULL)
	{
		m_pCLogHundler = new CLogger;
	}
	return *m_pCLogHundler;
}
