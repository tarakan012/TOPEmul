// TOPEmulator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "GateServer.h"

int main()
{
	try
	{
		GateServer gs;
		int n;
		std::cin >> n;
	}
	catch (boost::system::error_code ec)
	{
		return EXIT_FAILURE;
	}
    return EXIT_SUCCESS;
}

