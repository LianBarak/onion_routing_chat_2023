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
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = ::htons(CLIENTS_PORT); // Change to the desired port number
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // Listen on any available network interface

	if (::bind(_server_socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		int error = WSAGetLastError();
		char buffer[256];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buffer, sizeof(buffer), NULL);
		throw exception(buffer);
	}
		

	if (::listen(this->_server_socket, SOMAXCONN) == SOCKET_ERROR)
		throw exception("Error listening for incoming connections");
}



void ClientsCommunicator::handleNewClient(SOCKET client_socket)
{
	while (true) 
    {
		char buf[1024];
		int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
		if (bytes_received == SOCKET_ERROR)
			throw exception("Error receiving data from user");
		buf[bytes_received] = '\0'; // null-terminate the buffer 
		string decryptedBuf = decryptWithRSA(buf);
		this->_msgs.push(decryptedBuf.c_str());
	}
	closesocket(client_socket);
}
