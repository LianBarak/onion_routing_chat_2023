#pragma once
#ifndef CLIENTS_COMMUNICATOR_H
#define CLIENTS_COMMUNICATOR_H

#include "chachaCommunicator.h"

#define CLIENTS_PORT 8082
using namespace std;

class ClientsCommunicator
{
public:
	ClientsCommunicator(queue<const char*>& msgs);
	~ClientsCommunicator();
	void run();
private:
	SOCKET _server_socket;
	queue<const char*>& _msgs;
	void bindAndListen();
	void handleNewClient(SOCKET client_socket);
};

#endif
