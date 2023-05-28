#ifndef RSA_COMMUNICATOR_H
#define RSA_COMMUNICATOR_H

#include <fstream>
#include <WinSock2.h>
#include <exception>
#include <thread>
#include "JsonDesrialize.h"
#include "queue"

#define SERVER_PORT 8078
using namespace std;

class RsaCommunicator
{
public:
	RsaCommunicator(queue<const char*>& msgs);
	~RsaCommunicator();
	void run();
private:
	queue<const char*>& _msgs;
	SOCKET _server_socket;
	void bindAndListen();
	void handleNewClient(SOCKET client_socket);
};

#endif