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

	// 서버 연결 요청
	retval = connect(sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// 보낼 데이터
	std::vector<std::string> testdata = {
		"안녕하세요",
		"반가워요",
		"오늘따라 할 이야기가 많을 것 같네요",
		"저도 그렇네요"
	};

	// 데이터 송신
	for (auto& msg : testdata) {
		std::string sendData = msg + "\n"; // 개행 추가
		retval = send(sock, sendData.c_str(), static_cast<int>(sendData.size()), 0);
		if (retval == SOCKET_ERROR) err_display("send()");
		break;
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}