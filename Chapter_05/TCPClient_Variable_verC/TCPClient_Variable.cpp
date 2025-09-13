#include "../../Chapter_01/Common.h"
#include <WS2tcpip.h>
#include <string>
#include <vector>
#include <iostream>

constexpr const char* SERVERIP = "127.0.0.1";
constexpr int SERVERPORT = 9000;
constexpr int BUFSIZE = 50;

int main(int argc, char* argv[])
{
	int retval = 0;

	std::string serverIP = (argc > 1) ? argv[1] : SERVERIP;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		err_quit("socket()");
	}

	struct sockaddr_in serveraddr {};	
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, serverIP.c_str(), &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);

	// ���� ���� ��û
	retval = connect(sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// ���� ������
	std::vector<std::string> testdata = {
		"�ȳ��ϼ���",
		"�ݰ�����",
		"���õ��� �� �̾߱Ⱑ ���� �� ���׿�",
		"���� �׷��׿�"
	};

	// ������ �۽�
	for (auto& msg : testdata) {
		std::string sendData = msg + "\n"; // ���� �߰�
		retval = send(sock, sendData.c_str(), static_cast<int>(sendData.size()), 0);
		if (retval == SOCKET_ERROR) err_display("send()");
		break;
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}