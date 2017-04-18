// TOPEmulator.cpp: определяет точку входа для консольного приложения.
//

#include "TCPserver.h"

using namespace std;

int main()
{
	cout << "Start Emulator..." << endl;
	try
	{
		CLogHandler::GetInstance().Init();
		LOG_INFO("Log_info %d", 10);
		TCPServer<TCPSession> server;
		server.start_server();
		for (;;) { Sleep(1); }
	}
	catch (const std::exception e)
	{
		cerr << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
    return EXIT_SUCCESS;
		
}

