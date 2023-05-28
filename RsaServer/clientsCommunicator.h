#pragma once
#ifndef CLIENTS_COMMUNICATOR_H
#define CLIENTS_COMMUNICATOR_H

#include <iostream>
#include <fstream>
#include <WinSock2.h>
#include "Rsa_function.h"
#include <exception>
#include <queue>
#include <thread>

#define CLIENTS_PORT 8088
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