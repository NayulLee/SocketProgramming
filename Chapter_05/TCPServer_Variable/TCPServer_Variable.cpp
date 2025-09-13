#include "../../Chapter_01/Common.h"
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <stdexcept>
#include <vector>

constexpr int SERVERPORT = 9000;
constexpr int BUFSIZE = 512;

// ���� ������ �Լ�
int _recv_ahead(SOCKET s, char& c)
{
	thread_local std::vector<char> buf(1024);
	thread_local int nbytes = 0;
	thread_local int index = 0;

	if (nbytes == 0 || nbytes == SOCKET_ERROR)
	{
		nbytes = recv(s, buf.data(), static_cast<int>(buf.size()), 0);
		if (nbytes == SOCKET_ERROR) return SOCKET_ERROR;
		else if (nbytes == 0) return 0;
		index = 0;
	}

	c = buf[index++];
	--nbytes;
	return 1;
}

int recvline(SOCKET s, std::string& out, int maxlen)
{
	out.clear();
	char c;
	int nbytes;
	for (int n = 1; n < maxlen; n++)
	{
		nbytes = _recv_ahead(s, c);
		if (nbytes == 1)
		{
			out.push_back(c);
			if (c == '\n')
				break;
		}
		else if (nbytes == 0)
		{
			return static_cast<int>(out.size());
		}
		else
			return SOCKET_ERROR;
	}
	return static_cast<int>(out.size());
}

int main(int argc, char* argv[])
{
	int retval;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr{};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
	if (retval = SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval = SOCKET_ERROR) err_quit("listen()");

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	sockaddr_in clientaddr{};
	int addrlen;
	std::string buf;

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
		std::cout << "\n[TCP����] Ŭ���̾�Ʈ ���� : IP�ּ�=" << addr
			<< ", ��Ʈ��ȣ=" << ntohs(clientaddr.sin_port) << "\n";

		// Ŭ���̾�Ʈ�� ������ ���
		while (true)
		{
			// ������ �ޱ�
			int retval = recvline(client_sock, buf, BUFSIZE + 1);
			if (retval == SOCKET_ERROR) {
				std::cerr << "recv() ����\n";
				break;
			}
			else if (retval == 0)
				break;

			// ���� ������ ���
			std::cout << "[TCP/" << addr << ":" << ntohs(clientaddr.sin_port) << "] " << buf;
		}

		closesocket(client_sock);
		std::cout << "[TCP����] Ŭ���̾�Ʈ ����: IP�ּ�=" << addr
			<< ", ��Ʈ��ȣ=" << ntohs(clientaddr.sin_port) << "\n";
	}

	closesocket(listen_sock);
	WSACleanup();
	return 0;
}