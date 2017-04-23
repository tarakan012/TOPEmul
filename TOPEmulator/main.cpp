// TOPEmulator.cpp: определяет точку входа для консольного приложения.
//

#include "GameApp.h"
#include "TOPServer.h"

CGameApp * g_pCGameApp = nullptr;

using namespace std;

int main()
{

	cout << "Start Emulator..." << endl;
	try
	{
		g_pCGameApp = new CGameApp();
		g_pCGameApp->IniMap();
		if (nullptr == g_pCGameApp->FindMapByName("garner"))
		{
			throw std::invalid_argument("NO find Map");
		}
		CLogHandler::GetInstance().Init();
		LOG_INFO("Log_info %d", 10);
		if (!TOPServer::CreateInstance())
		{
			cout << "Start Emulator FAIL!" << endl;
		}
		TOPServer::Instance()->Init();

		for (;;) { Sleep(1); }
	}
	catch (const std::exception e)
	{
		cerr << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
    return EXIT_SUCCESS;
		
}

