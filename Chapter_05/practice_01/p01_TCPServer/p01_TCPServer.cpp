/*
	이 예제를 수정하여 간단한 채팅 프로그램을 작성하려고 한다.
	채팅 ID는 서버와 클라이언트 모두 명령행 인수로 입력받으며, 
	항상 클라이언트 → 서버 → 클라 → 서버 → 클라 .. 순으로 채팅 메시지를 입력하는 것으로 가정한다
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
	std::string serverID; // 서버ID
	int retval = 0;

	// 명령행 인수 체크
	if (argc != 2)
	{
		std::cout << "사용법 : 프로그램명 <채팅ID>" << std::endl;
		return 1;
	}

	serverID = argv[1];
	std::cout << "채팅 ID : " << serverID << std::endl;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// 포트 바인딩
	struct sockaddr_in serveraddr {};
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수 
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

		// 접속한 클라이언트 정보 출력
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		std::cout << "\n[TCP 서버 클라이언트 접속] : "
			<< "IP주소 = " << addr
			<< ", 포트 번호 = " << ntohs(clientaddr.sin_port) << std::endl;

		// 클라이언트 ID받기
		retval = recv(client_sock, buf.data(), BUFSIZE, MSG_WAITALL);
		if (retval == SOCKET_ERROR || retval == 0) break;
		
		std::string clientID;
		buf[retval] = '\0';
		clientID = buf.data(); // 클라이언트 id저장
		std::cout << "[클라이언트 접속] ID : " << clientID << std::endl;


		while (true)
		{
			//  1. 클라이언트 메시지 받기
			retval = recv(client_sock, buf.data(), BUFSIZE, MSG_WAITALL);
			if (retval == SOCKET_ERROR || retval == 0) break;

			buf[retval] = '\0'; // 문자열의 끝을 표시
			std::cout << "[" << clientID << "] : " << buf.data() << std::endl;
			
			// 2. 서버 메시지 입력 후 전송
			std::cout << "[" << serverID << "] 메시지 입력";
			std::string serverMsg;
			std::getline(std::cin, serverMsg);

			// 고정 길이로 패딩해서 전송
			std::string sendBuffer(BUFSIZE, '#');
			std::copy_n(serverMsg.begin(), )
		}

	}

}