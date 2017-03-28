// TOPEmulator.cpp: определяет точку входа для консольного приложения.
//

#include "TCPserver.h"

using namespace std;

int main()
{
		cout << "Start Emulator" << endl;
	try
	{
		//g_conpq = new pqxx::connection("dbname=noterius user=nota host=127.0.0.1 password=notadefault");
		
		TCPServer<TCPSession> server;
		server.start_server();
		
	}
	catch (const std::exception e)
	{
		cerr << "Error: " << e.what() << endl;
		return EXIT_FAILURE;
	}
    return EXIT_SUCCESS;
		
}

