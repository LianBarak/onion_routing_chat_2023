#pragma once
#ifndef SERVER_COMMUNICATOR_H
#define SERVER_COMMUNICATOR_H

#include "clientsCommunicator.h"
#define SERVER_PORT 8078

using namespace std;

class ServerCommunicator
{
public:
	ServerCommunicator(queue<const char*>& msgs);
	~ServerCommunicator();
	void handleServer();
private:
	SOCKET _server_socket;
	queue<const char*>& _msgs;

	void connect();
};

#endif