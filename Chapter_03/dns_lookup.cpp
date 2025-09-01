/*  1. gethostbyname()���� ������ �̸��� ��ȸ
*	2. hostent ����ü�� �޴´�
*	3. ����ü���� ������ �Ϲ�, ��Ī, IP�ּҸ� �о� ���ڿ��� ���
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>	// winsock �⺻ �ڷ����� �Լ�(WSAStartup, WSACleanup...)
#include <WS2tcpip.h>	// inet_ntop, AF_INET���� ����

#pragma comment(lib, "ws2_32.lib") // MSVC: ������ �� ws2_32.lib(���� ���̺귯��)�� �ڵ� ��ũ

int main()
{
	// ���� �ʱ�ȭ
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup failed" << std::endl;
		return 1;
	}

	const char* domain = "www.google.com";	// ��ȸ�� ������ �̸�(���ڿ�)

	// ������ �� IP�� ��ȯ
	hostent* host = gethostbyname(domain);
	if (host == nullptr)
	{
		std::cerr << "gethostbyname failed" << std::endl;
		WSACleanup();
		return 1;
	}

	std::cout << "���� ������ �̸� : " << host->h_name << std::endl;

	// alias ���
	for (int i = 0; host->h_aliases[i] != nullptr; i++)
	{
		std::cout << "��Ī : " << host->h_aliases[i] << std::endl;
	}

	// IP�ּ� ���
	for (int i = 0; host->h_addr_list[i] != nullptr; i++)
	{
		char ip[INET_ADDRSTRLEN]; // IPv4 ���ڿ��� ������ ����(���� 16����Ʈ)
		inet_ntop(AF_INET, host->h_addr_list[i], ip, sizeof(ip));
		std::cout << "IP�ּ� : " << ip << std::endl;
	}

	// ���� ����
	WSACleanup();
	return 0;
}