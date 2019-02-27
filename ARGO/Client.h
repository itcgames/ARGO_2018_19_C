#pragma once

#include <iostream>
#include <string>
#include <WS2tcpip.h>

struct NetworkMessage
{
	int type = -1;
	int playerIndex = 5;
	int hostIndex = -1;
	bool ready = false;
	int x = -10;
	int y = -10;
	//std::string state = "";
	//std::string msg = "";
};


class Client
{
public:
	Client();
	~Client();
	void init(std::string ip);
	bool run();
	std::string receive();
	void sendMsg(std::string msg);
	void sendFinalMsg();
	void close();

private:
	std::string ipAddress;
	int port;
	WSAData data;
	WORD ver;
	int wsResult;
	SOCKET sock; 
	sockaddr_in hint;
	int connResult;
	char buf[4096];
	std::string userInput;
	void sendIP();
	std::string m_message;
};