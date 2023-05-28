#include "AesCommunicator.h"


ServerCommunicator::ServerCommunicator(queue<const char*>& msgs) :_msgs(msgs)
{

	this->_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_server_socket == INVALID_SOCKET)
		throw exception("error creating socket");
}

ServerCommunicator::~ServerCommunicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(this->_server_socket);
	}
	catch (...) {}
}

void ServerCommunicator::handleServer()
{
	connect();

	while (true) {
		for (int i = 0; i < this->_msgs.size(); i++)
		{
			const char* message = this->_msgs.front();
			this->_msgs.pop();

			if (!send(this->_server_socket, message, strlen(message), 0))
				throw exception("Error sending message");
		}

	}
}

void ServerCommunicator::connect()
{
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = ::htons(AES_PORT);

	if (::connect(this->_server_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw exception("Error connecting chacha server");
}
