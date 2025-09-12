#define NOMINMAX
#include "../../Chapter_01/Common.h"
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <algorithm>
#include <vector>

std::string SERVERIP = "127.0.0.1";	
constexpr int SERVERPORT = 9000;
constexpr int BUFSIZE = 50;

int main(int argc, char* argv[])
{
	int retval;

	// 명령행 인수가 있으면 IP주소로 사용한다
	std::vector<std::string> args(argv, argv + argc);
	if (argc > 1) SERVERIP = argv[1];

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	struct sockaddr_in serveraddr = {};
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, SERVERIP.c_str(), &serveraddr.sin_addr);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// 데이터 통신에 사용할 변수
	std::vector<std::string> testdata = {
		"안녕하세요",
		"반가워요",
		"오늘따라 할 이야기가 많을 것 같네요",
		"저도 그렇네요"
	};

	// 서버와 데이터 통신
	for (const auto& msg : testdata)
	{
		std::string buffer(BUFSIZE, '#');
		std::copy_n(msg.begin(),
					std::min(static_cast<int>(msg.size()), BUFSIZE),
					buffer.begin());

		retval = send(sock, buffer.data(), BUFSIZE, 0);
		if (retval == SOCKET_ERROR) {
			err_display("send()");
			break;
		}

		std::cout << "[TCP클라이언트] " << retval << "바이트를 보냈습니다. "
			<< "원본 메시지: " << msg << std::endl;
	}

	closesocket(sock);

	WSACleanup();
	return 0;
}