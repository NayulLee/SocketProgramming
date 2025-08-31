#include "..\Chapter_01\Common.h"
#include <iostream>
#include <WS2tcpip.h>

int main(int argc, char* argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// IPv4 ��ȯ ����
	// ������ IPv4 �ּ� ���
	const char* ipv4test = "147.46.114.70";
	std::cout << "IPv4 �ּ�(��ȯ ��) : " << ipv4test << std::endl;

	// inet_pton() �Լ� ����
	struct in_addr ipv4num;
	inet_pton(AF_INET, ipv4test, &ipv4num);
	std::cout << "inet_pton() �Լ��� ��ȯ �� : " << ipv4num.s_addr << std::endl;

	// inet_ntop() �Լ� ����
	char ipv4str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipv4num, ipv4str, sizeof(ipv4str));
	std::cout << "IPv4 �ּ�(�ٽ� ��ȯ ��) : " << ipv4str << std::endl;

	// ���� ����
	WSACleanup();
	return 0;
}