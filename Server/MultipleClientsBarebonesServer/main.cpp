#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <vector>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

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

void main()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	std::vector<std::string> lobby;
	std::vector<std::string> lobbyBuf;
	std::vector<SOCKET> lobbySocks;
	std::vector<std::vector<int>> lobbies;
	
	std::vector<int> temp;
	for (int i = 0; i < 4; i++)
	{
		temp.push_back(-1);
	}
	lobbies.push_back(temp);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return;
	}
	
	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 
	
	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);

	// Create the master file descriptor set and zero it
	fd_set master;
	FD_ZERO(&master);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	FD_SET(listening, &master);

	// this will be changed by the \quit command (see below, bonus not in video!)
	bool running = true; 
	int numPlayers = 0;

	while (running)
	{		
		fd_set copy = master;
		NetworkMessage * welcomeMessage = new NetworkMessage();

		// See who's talking to us
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			// Makes things easy for us doing this assignment
			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication?
			if (sock == listening)
			{
				// Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);

				// Add the new connection to the list of connected clients
				FD_SET(client, &master);

				// Send a welcome message to the connected client
				string welcomeMsg = "Joined Game";

				welcomeMessage->type = 0;

				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
				//send(client,(char*)welcomeMessage, sizeof(struct NetworkMessage) + 1, 0);
			}
			else // It's an inbound message
			{
				char buf[4096];
				ZeroMemory(buf, 4096);
				
				// Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					for (int i = 0; i < lobbySocks.size(); i++)
					{
						if (sock == lobbySocks[i])
						{
							lobbySocks.erase(lobbySocks.begin() + i);
							lobby.erase(lobby.begin() + i);

							break;
						}
					}
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					// Check to see if it's a command. \quit kills the server
					if (buf[0] == '\\')
					{
						// Is the command quit? 
						string cmd = string(buf, bytesIn);
						if (cmd == "\\quit")
						{
							running = false;
							break;
						}

						// Unknown command
						continue;
					}
					std::string message = buf;
					// Tell player if they are the host or a client
					int indexIP = message.find("IP:");
					int indexQ = message.find("What is my Index");
					int indexPlayer = message.find("Player");
					int indexLobby = message.find("Lobby");
					int indexPU = message.find("Power Ups");
					int indexFlag = message.find("Flag");
					if (indexIP > 0)
					{
						std::cout << message << std::endl;
						if (lobby.size() == 0)
						{
							// host
							lobby.push_back(message);
							lobbySocks.push_back(sock);
							std::string msg = "Host";
							NetworkMessage netMsg;
							netMsg.type = 1; // Joining
							netMsg.playerIndex = 0;
							netMsg.hostIndex = lobby.size() - 1;
							send(sock, msg.c_str(), msg.size() + 1, 0);
						}
						else if (lobby.size() % 4 == 0)
						{
							// host
							lobby.push_back(message);
							lobbySocks.push_back(sock);
							std::string msg = "Host";
							NetworkMessage netMsg;
							netMsg.type = 1; // Joining
							netMsg.playerIndex = 0;
							netMsg.hostIndex = lobby.size() - 1;
							send(sock, msg.c_str(), msg.size() + 1, 0);
						}
						else if(lobby.size() % 4 > 0)
						{
							//client
							std::string hostMsg = "Joining host: " + std::to_string(lobby.size() % 4) + " Host IP: " + lobby[lobby.size() - (lobby.size() % 4)];
							// Send the host IP so the player can join
							lobby.push_back(message);
							lobbySocks.push_back(sock);

							NetworkMessage netMsg;
							netMsg.type = 1; // Joining
							netMsg.playerIndex = lobby.size() % 4;
							netMsg.hostIndex = lobby.size() - (lobby.size() % 4);
							send(sock, hostMsg.c_str(), hostMsg.size() + 1, 0);

						}
					}
					else if (indexQ >= 0)
					{
						for (int i = 0; i < lobbySocks.size(); i++)
						{
							if (sock == lobbySocks[i])
							{
								//client
								std::string hostMsg = "Joining host: " + std::to_string(i % 4) + " Host IP: " + lobby[i - (i % 4)];
								NetworkMessage netMsg;
								netMsg.type = 1; // Joining
								netMsg.playerIndex = i % 4;
								netMsg.hostIndex = i - (i % 4);
								// Send the host IP so the player can join
								send(sock, hostMsg.c_str(), hostMsg.size() + 1, 0);
							}
						}
					}// Send message to other clients, and definiately NOT the listening socket
					else if (indexPlayer >= 0) // || buf[0] == 'X')
					{
						std::cout << buf << std::endl;

						for (int i = 0; i < master.fd_count; i++)
						{
							SOCKET outSock = master.fd_array[i];
							if (outSock != listening && outSock != sock)
							{
								ostringstream ss;
								ss << "SOCKET #" << sock << ": " << buf << "\r\n";
								string strOut = ss.str();

								send(outSock, strOut.c_str(), strOut.size() + 1, 0);
							}
						}
					}
					else if (indexLobby >= 0 || buf[6] == 'i')
					{
						std::cout << buf << std::endl;

						if (buf[17] == '0')
						{
							// Left lobby
							int leftIndex = (int)buf[3] - 48;
							std::cout << "Left lobby: ";
							std::cout << buf[3] << std::endl;

							for (int i = 0; i < lobbySocks.size(); i++)
							{
								if (sock == lobbySocks[i])
								{
									std::cout << "Index: " << std::to_string(i) << std::endl;
								}
							}
							

						}

						lobbyBuf.push_back(buf);

						bool ready = true;

						if ((int)buf[3] % 4 == 3)
						{
							for (int i = 3; i < lobbySocks.size(); )
							{	
								if (i < lobbySocks.size())
								{
									if (sock == lobbySocks[i])
									{

										ready = true;
										// Check if the host is ready
										if (lobbyBuf[0][12] == '0')
										{
											ready = false;
										}
										// Check if player 2 is ready
										if (lobbyBuf[1][12] == '0')
										{
											ready = false;
										}
										// Check if player 3 is ready
										if (lobbyBuf[2][12] == '0')
										{
											ready = false;
										}
										// Check if player 4 is ready
										if (lobbyBuf[3][12] == '0')
										{
											ready = false;
										}
									}
								}
								i = i + 4;
							}
						}
						
						if (ready == false || (int)buf[3] % 4 != 3)
						{
							for (int i = 0; i < master.fd_count; i++)
							{
								SOCKET outSock = master.fd_array[i];
								if (outSock != listening && outSock != sock)
								{
									ostringstream ss;
									ss << buf << "\r\n";
									string strOut = ss.str();

									send(outSock, strOut.c_str(), strOut.size() + 1, 0);
								}
							}
						}
					}
					else if (indexPU >= 0 || message.substr(0, 9) == "Power Ups")
					{
						std::cout << buf << std::endl;

						for (int i = 0; i < master.fd_count; i++)
						{
							SOCKET outSock = master.fd_array[i];
							if (outSock != listening && outSock != sock)
							{
								ostringstream ss;
								ss << buf;
								string strOut = ss.str();

								send(outSock, strOut.c_str(), strOut.size() + 1, 0);
							}
						}
					}
					else if (indexFlag >= 0 || message.substr(0, 5) == "Flag ")
					{
						for (int i = 0; i < master.fd_count; i++)
						{
							SOCKET outSock = master.fd_array[i];
							if (outSock != listening && outSock != sock)
							{
								ostringstream ss;
								ss << buf;
								string strOut = ss.str();

								send(outSock, strOut.c_str(), strOut.size() + 1, 0);
							}
						}
					}
					
				}
			}
		}
	}

	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	FD_CLR(listening, &master);
	closesocket(listening);
	
	// Message to let users know what's happening.
	string msg = "Server is shutting down. Goodbye\r\n";

	NetworkMessage netMsg;
	//netMsg.type = "Closing";

	netMsg.type = 3; // Closing
	//netMsg.msg = "Server is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)
	{
		// Get the socket number
		SOCKET sock = master.fd_array[0];

		// Send the goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &master);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();

	system("pause");
}