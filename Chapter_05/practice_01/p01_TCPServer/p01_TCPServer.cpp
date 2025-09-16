/*
	�� ������ �����Ͽ� ������ ä�� ���α׷��� �ۼ��Ϸ��� �Ѵ�.
	ä�� ID�� ������ Ŭ���̾�Ʈ ��� ����� �μ��� �Է¹�����, 
	�׻� Ŭ���̾�Ʈ �� ���� �� Ŭ�� �� ���� �� Ŭ�� .. ������ ä�� �޽����� �Է��ϴ� ������ �����Ѵ�
*/
#include "../../../Chapter_01/Common.h"
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>

constexpr int SERVERPORT = 9000;
constexpr int BUFSIZE = 50;

int main(int argc, char* argv[])
{	
	std::string serverID; // ����ID
	int retval = 0;

	// ����� �μ� üũ
	if (argc != 2)
	{
		std::cout << "���� : ���α׷��� <ä��ID>" << std::endl;
		return 1;
	}

	serverID = argv[1];
	std::cout << "ä�� ID : " << serverID << std::endl;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// ��Ʈ ���ε�
	struct sockaddr_in serveraddr {};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ������ ��ſ� ����� ���� 
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	std::vector<char> buf(BUFSIZE + 1);

	while (true)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, reinterpret_cast<sockaddr*>(&clientaddr), &addrlen);
		if(client_sock == INVALID_SOCKET) 
		{
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		std::cout << "\n[TCP ���� Ŭ���̾�Ʈ ����] : "
			<< "IP�ּ� = " << addr
			<< ", ��Ʈ ��ȣ = " << ntohs(clientaddr.sin_port) << std::endl;

		// Ŭ���̾�Ʈ ID�ޱ�
		retval = recv(client_sock, buf.data(), BUFSIZE, MSG_WAITALL);
		if (retval == SOCKET_ERROR || retval == 0) break;
		
		std::string clientID;
		buf[retval] = '\0';
		clientID = buf.data(); // Ŭ���̾�Ʈ id����
		std::cout << "[Ŭ���̾�Ʈ ����] ID : " << clientID << std::endl;


		while (true)
		{
			//  1. Ŭ���̾�Ʈ �޽��� �ޱ�
			retval = recv(client_sock, buf.data(), BUFSIZE, MSG_WAITALL);
			if (retval == SOCKET_ERROR || retval == 0) break;

			buf[retval] = '\0'; // ���ڿ��� ���� ǥ��
			std::cout << "[" << clientID << "] : " << buf.data() << std::endl;
			
			// 2. ���� �޽��� �Է� �� ����
			std::cout << "[" << serverID << "] �޽��� �Է�";
			std::string serverMsg;
			std::getline(std::cin, serverMsg);

			// ���� ���̷� �е��ؼ� ����
			std::string sendBuffer(BUFSIZE, '#');
			std::copy_n(serverMsg.begin(), )
		}

	}

}