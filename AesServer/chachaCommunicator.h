#pragma once
#ifndef CHACHA_COMMUNICATOR_H
#define CHACHA_COMMUNICATOR_H

#include <fstream>
#include <WinSock2.h>
#include <exception>
#include <thread>
#include "JsonDesrialize.h"
#include "queue"

#define SERVER_PORT 8070
using namespace std;

class ChachaCommunicator
{
public:
	ChachaCommunicator(queue<const char*>& _msgs);
	~ChachaCommunicator();
	void run();
private:
	queue<const char*>& _msgs;
	SOCKET _server_socket;
	void bindAndListen();
	void handleNewClient(SOCKET client_socket);
};

#endif