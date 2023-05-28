#ifndef AES_COMMUNICATOR_H
#define AES_COMMUNICATOR_H

#include "rsaCommunicator.h"

#define AES_PORT 8070
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