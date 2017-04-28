// TOPEmulator.cpp: определяет точку входа для консольного приложения.
//

#include "GameApp.h"
#include "TOPServer.h"
#include "GameDB.h"

CGameApp * g_pCGameApp = nullptr;


int main()
{
	try
	{
		cout << "Start Emulator..." << endl;

		g_pCGameApp = new CGameApp();
		g_pCGameApp->Init();

		thread HandleMove(g_GameLogicProcess);


		CLogger::GetInstance().Init();
//		LOG_INFO("Log_info %d", 10);
		if (!TOPServer::CreateInstance())
		{
			cout << "Start Emulator FAIL!" << endl;
		}
		TOPServer::Instance()->Init();
		string strOutCin;
		while (getline(cin, strOutCin))
		{
			if (strOutCin == "exit") exit(0);
		}
	}
	catch (const std::exception e)
	{
		cerr << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
    return EXIT_SUCCESS;
		
}

