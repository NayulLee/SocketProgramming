#pragma comment(lib, "ws2_32.lib")  // �ݵ�� �߰�

#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa); // ���� �ʱ�ȭ

	sockaddr_in serverAddr; // ���� �ּ� ����ü ����
	serverAddr.sin_family = AF_INET;	//IPv4
	serverAddr.sin_port = htons(9000);	// ��Ʈ��ȣ 9000, ��Ʈ��ũ ����Ʈ ������ ��ȯ
	InetPton(AF_INET, L"127.0.0.1", &serverAddr.sin_addr); // �ֽ� ������� IP ��ȯ
	memset(serverAddr.sin_zero, 0, sizeof(serverAddr.sin_zero)); // 0���� �ʱ�ȭ

	std::cout << "���� �ּ� ����ü ���� �Ϸ�!" << std::endl;

	WSACleanup();
	return 0;
}