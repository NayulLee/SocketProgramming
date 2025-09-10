#include "../../Chapter_01/Common.h"
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <vector>

std::string SERVERIP = "127.0.0.1";	
constexpr int SERVERPORT = 9000;
constexpr int BUFSIZE = 50;

int main(int argc, char* argv[])
{
	int retval;

	// ����� �μ��� ������ IP�ּҷ� ����Ѵ�
	std::vector<std::string> args(argv, argv + argc);
	if (argc > 1) SERVERIP = argv[1];

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr = {};
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP.c_str(), &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// ������ ��ſ� ����� ����
	std::vector<std::string> testdata = {
		"�ȳ��ϼ���",
		"�ݰ�����",
		"���õ��� �� �̾߱Ⱑ ���� �� ���׿�",
		"���� �׷��׿�"
	};

	// ������ ������ ���
	for (int i = 0; i < 4; i++)
	{
		memset(buf, '#', sizeof(buf));
		strncpy(buf, testdata[i], strlen(testdata[i]));
	}




}