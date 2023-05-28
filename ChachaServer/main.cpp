#pragma comment (lib, "ws2_32.lib")
#include "AesCommunicator.h"
#include <Windows.h>

int main()
{
	std::cout << "Starting...";
	try
	{

		WSADATA wsa_data = { };
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
			throw std::exception("WSAStartup Failed");

		queue<const char*> msgs;
		RsaCommunicator* rsaCom = new RsaCommunicator(msgs);
		ServerCommunicator* aesCom = new ServerCommunicator(msgs);


		std::thread t_r_connector(&RsaCommunicator::run, rsaCom);
		std::thread t_s_connector(&ServerCommunicator::handleServer, aesCom);

		t_r_connector.detach();
		t_s_connector.detach();


		try
		{
			WSACleanup();
		}
		catch (...) {}
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");


	return 0;
}
