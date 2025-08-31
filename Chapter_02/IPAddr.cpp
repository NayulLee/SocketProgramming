#include "..\Chapter_01\Common.h"
#include <iostream>
#include <WS2tcpip.h>

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// IPv4 변환 연습
	// 원래의 IPv4 주소 출력
	const char* ipv4test = "147.46.114.70";
	std::cout << "IPv4 주소(변환 전) : " << ipv4test << std::endl;

	// inet_pton() 함수 연습
	struct in_addr ipv4num;
	inet_pton(AF_INET, ipv4test, &ipv4num);
	std::cout << "inet_pton() 함수로 변환 후 : " << ipv4num.s_addr << std::endl;

	// inet_ntop() 함수 연습
	char ipv4str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipv4num, ipv4str, sizeof(ipv4str));
	std::cout << "IPv4 주소(다시 변환 후) : " << ipv4str << std::endl;

	// 윈속 종료
	WSACleanup();
	return 0;
}