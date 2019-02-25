#include "Client.h"
#include <string>
#include <fstream>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

Client::Client()
{
	//ipAddress = "149.153.106.162";			// IP Address of the server (Jack)
	//ipAddress = "149.153.106.161";			// IP Address of the server (Jake)
	//ipAddress = "149.153.106.163";			// IP Address of the server (Jamie)


//	ipAddress = "149.153.106.161";			// IP Address of the server (Jake)
	//ipAddress = "149.153.106.161";			// IP Address of the server (Jamie)
=======

	port = 54000;						// Listening port # on the server

										// Initialize WinSock
	ver = MAKEWORD(2, 2);
	wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
		return;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

}

Client::~Client()
{

}

void Client::init(std::string ip)
{
	ipAddress = ip;			// IP Address of the server
	port = 54000;						// Listening port # on the server

											// Initialize WinSock
	ver = MAKEWORD(2, 2);
	wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
		return;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
}

bool Client::run()
{
	// Connect to server
	connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return false;
	}
	u_long iMode = 1;
	ioctlsocket(sock, FIONBIO, &iMode);
	return true;
}

std::string Client::receive()
{
	ZeroMemory(buf, 4096);

	//NetworkMessage * netMsg = new NetworkMessage();

	int bytesReceived = recv(sock, buf, 4096, 0);
	//int bytesReceived = recv(sock, (char*)netMsg, sizeof(struct NetworkMessage) + 1, 0);
	if (bytesReceived > 0)
	{
		// Echo response to console
		std::string msg = buf;
		if ((std::string)buf == "Joined Game")
		{
			std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
			sendIP();

		}
		else if ((std::string)buf == "Host")
		{
			// Host server
			std::cout << "Host" << std::endl;
		}
		else if (msg.substr(0, 8) == "Joining ")
		{
			std::cout << msg << std::endl;

		}
		return buf;
	}
	return "";
}

void Client::sendMsg(std::string msg)
{
	int sendResult = send(sock, msg.c_str(), msg.size() + 1, 0);
}

void Client::close()
{
	// Send message letting server know you're leaving
	std::string msg = "Leaving: "; // + serverIndex
	sendMsg(msg);
	closesocket(sock);
	WSACleanup();
}

void Client::sendIP()
{
	std::string line;
	std::ifstream IPFile;
	int offset;
	const char* search0 = "IPv4 Address. . . . . . . . . . . :";      // search pattern

	system("ipconfig > ip.txt");

	IPFile.open("ip.txt");
	if (IPFile.is_open())
	{
		while (!IPFile.eof())
		{
			getline(IPFile, line);
			if ((offset = line.find(search0, 0)) != std::string::npos)
			{
				//   IPv4 Address. . . . . . . . . . . : 1
				//1234567890123456789012345678901234567890
				line.erase(0, 39);
				sendMsg("IP: " + line);
				IPFile.close();
			}
		}
	}
}
