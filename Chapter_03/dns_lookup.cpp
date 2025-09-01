/*  1. gethostbyname()으로 도메인 이름을 조회
*	2. hostent 구조체를 받는다
*	3. 구조체에서 도메인 일므, 별칭, IP주소를 읽어 문자열로 출력
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>	// winsock 기본 자료형과 함수(WSAStartup, WSACleanup...)
#include <WS2tcpip.h>	// inet_ntop, AF_INET같은 정의

#pragma comment(lib, "ws2_32.lib") // MSVC: 컴파일 시 ws2_32.lib(윈속 라이브러리)를 자동 링크

int main()
{
	// 윈속 초기화
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed" << std::endl;
		return 1;
	}

	const char* domain = "www.google.com";	// 조회할 도메인 이름(문자열)

	// 도메인 → IP로 변환
	hostent* host = gethostbyname(domain);
	if (host == nullptr)
	{
		std::cerr << "gethostbyname failed" << std::endl;
		WSACleanup();
		return 1;
	}

	std::cout << "공식 도메인 이름 : " << host->h_name << std::endl;

	// alias 출력
	for (int i = 0; host->h_aliases[i] != nullptr; i++)
	{
		std::cout << "별칭 : " << host->h_aliases[i] << std::endl;
	}

	// IP주소 출력
	for (int i = 0; host->h_addr_list[i] != nullptr; i++)
	{
		char ip[INET_ADDRSTRLEN]; // IPv4 문자열을 저장할 버퍼(보통 16바이트)
		inet_ntop(AF_INET, host->h_addr_list[i], ip, sizeof(ip));
		std::cout << "IP주소 : " << ip << std::endl;
	}

	// 윈속 종료
	WSACleanup();
	return 0;
}