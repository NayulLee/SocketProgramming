#include "../../Chapter_01/Common.h"
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <vector>

constexpr int SERVERPORT = 9000;
constexpr int BUFSIZE = 50;

int main(int argc, char* argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
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
		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		std::cout << "\n[TCP ���� Ŭ���̾�Ʈ ����] : "
			<< "IP�ּ� = " << addr
			<< ", ��Ʈ ��ȣ = " << ntohs(clientaddr.sin_port)<<std::endl;

		while (true)
		{
			// Ŭ���̾�Ʈ�� ������ ���
			retval = recv(client_sock, buf.data(), BUFSIZE, MSG_WAITALL);
			if (retval == SOCKET_ERROR)
			{
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			// ���� ������ ���
			buf[retval] = '\0'; // ���ڿ� �� ǥ��
			std::cout << "[TCP " << addr << " : " << ntohs(clientaddr.sin_port)
				<< "]" << buf.data() << std::endl;
		}
		// ���� �ݱ�
		closesocket(client_sock);
		std::cout << "[TCP����] Ŭ���̾�Ʈ ���� : IP�ּ� = " << addr
			<< ", ��Ʈ ��ȣ = " << ntohs(clientaddr.sin_port) << std::endl;
	}
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}