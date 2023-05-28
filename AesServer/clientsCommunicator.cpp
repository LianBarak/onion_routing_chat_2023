#pragma once
#include "clientsCommunicator.h"


ClientsCommunicator::ClientsCommunicator(queue<const char*>& msgs) : _msgs(msgs)
{
	this->_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_server_socket == INVALID_SOCKET)
		throw exception("error creating socket");
}

ClientsCommunicator::~ClientsCommunicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(this->_server_socket);
	}
	catch (...) {}
}

void ClientsCommunicator::run()
{
	bindAndListen();

	while (true) {
		SOCKET clientSocket = ::accept(this->_server_socket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET)
			throw std::exception("Error excepting socket");

		thread clientThread(&ClientsCommunicator::handleNewClient, this, clientSocket);
		clientThread.detach();
	}
}



void ClientsCommunicator::bindAndListen()
{
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = ::htons(CLIENTS_PORT);

	if (::bind(this->_server_socket, reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) == SOCKET_ERROR)
		throw exception("Error binding socket to address");

	if (::listen(this->_server_socket, SOMAXCONN) == SOCKET_ERROR)
		throw exception("Error listening for incoming connections");
}

void ClientsCommunicator::handleNewClient(SOCKET client_socket)
{
	try {
		while (true) {
			const char* message = this->_msgs.front();
			this->_msgs.pop();
			if (!send(client_socket, message, strlen((const char*)message), 0))
				throw(std::exception("socket closed"));
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
	closesocket(client_socket);
}
