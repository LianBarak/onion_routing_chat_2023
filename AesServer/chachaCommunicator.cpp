#include "chachaCommunicator.h"

ChachaCommunicator::ChachaCommunicator(queue<const char*>& msgs) :_msgs(msgs)
{
	this->_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_server_socket == INVALID_SOCKET)
		throw exception("error creating socket");
}

ChachaCommunicator::~ChachaCommunicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(this->_server_socket);
	}
	catch (...) {}
}

void ChachaCommunicator::run()
{
	
	bindAndListen();
	while (true) {
		sockaddr_in clientAddr;
		int clientAddrSize = sizeof(clientAddr);
		SOCKET clientSocket = accept(_server_socket, (sockaddr*)&clientAddr, &clientAddrSize);
		if (clientSocket == INVALID_SOCKET)
			throw exception("Error excepting client");


		// Verify that the client is the intended sender (assuming IP address is used for identification)
		if (clientAddr.sin_addr.s_addr != htonl(INADDR_LOOPBACK))
			throw exception("Connection from unauthorized IP address.");

		handleNewClient(clientSocket);
	}
}

void ChachaCommunicator::bindAndListen()
{
	try {
		struct sockaddr_in sa;
		sa.sin_family = AF_INET;
		sa.sin_addr.s_addr = INADDR_ANY;
		sa.sin_port = ::htons(SERVER_PORT);

		if (::bind(this->_server_socket, reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) == SOCKET_ERROR)
			throw exception("Error binding socket to address");

		if (::listen(this->_server_socket, SOMAXCONN) == SOCKET_ERROR)
			throw exception("Error listening for incoming connections");
	}
	catch (std::exception ex)
	{
		std::cout << "An exception occurred: " << ex.what() << std::endl;
	}
}

void ChachaCommunicator::handleNewClient(SOCKET client_socket)
{
	try
	{
		while (true)
		{
			char buf[1024];
			int bytes_received = recv(client_socket, buf, sizeof(buf), 0);
			if (bytes_received == SOCKET_ERROR)
				throw exception("Error receiving data from user");

			JsonDesrialize jd;
			Request req = jd.Desrialize(buf);

			mySqlConnector mysql;
			pair<const char*, const char*> ckey = mysql.getKey(req.id);
			const char* decBuffer = decryptBuffer(req.buffer, ckey.first, ckey.second);

			_msgs.push(decBuffer);
			mysql.deleteKey(req.id);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	closesocket(client_socket);
}
