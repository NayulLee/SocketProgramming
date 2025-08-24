#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void ErrorHandling(const char* message)
{
	cerr << message << " (���� �ڵ� : " << WSAGetLastError() << ")" << endl;
	exit(1);
}

int main()
{
	WSADATA wsaData;
	SOCKET hSocket;

	// ���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() ����");

	// ���� ����
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() ���� ����");

	cout << "���� ���� ����!" << endl;

	closesocket(hSocket);
	WSACleanup();
	return 0;
}