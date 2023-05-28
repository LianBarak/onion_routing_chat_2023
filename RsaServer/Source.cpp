#include "ServerCommunicator.h"
#include <Windows.h>

#pragma comment (lib, "ws2_32.lib")
int main()
{
	try {
		WSADATA wsa_data = { };
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
			throw std::exception("WSAStartup Failed");

	
		queue<const char*> msgs;
		ClientsCommunicator* clientsCom = new ClientsCommunicator(msgs);
		ServerCommunicator* serverCom = new ServerCommunicator(msgs);


		std::thread t_c_connector(&ClientsCommunicator::run, clientsCom);
		std::thread t_s_connector(&ServerCommunicator::handleServer, serverCom);

		t_c_connector.detach();
		t_s_connector.detach();

		try
		{
			WSACleanup();
		}
		catch (...) {}
	}
	catch (std::exception e) {
		std::cout << "Error occured: " << e.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}