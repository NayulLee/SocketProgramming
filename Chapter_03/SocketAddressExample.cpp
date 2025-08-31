#pragma comment(lib, "ws2_32.lib")  // 반드시 추가

#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // 윈속 초기화

	sockaddr_in serverAddr; // 서버 주소 구조체 생성
	serverAddr.sin_family = AF_INET;	//IPv4
	serverAddr.sin_port = htons(9000);	// 포트번호 9000, 네트워크 바이트 순서로 변환
	InetPton(AF_INET, L"127.0.0.1", &serverAddr.sin_addr); // 최신 방식으로 IP 변환
	memset(serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero)); // 0으로 초기화

	std::cout << "서버 주소 구조체 설정 완료!" << std::endl;

	WSACleanup();
	return 0;
}