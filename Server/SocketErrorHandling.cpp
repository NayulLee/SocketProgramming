#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void ErrorHandling(const char* message)
{
	cerr << message << " (俊矾 内靛 : " << WSAGetLastError() << ")" << endl;
	exit(1);
}

int main()
{
	WSADATA wsaData;
	SOCKET hSocket;

	// 扩加 檬扁拳
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() 角菩");

	// 家南 积己
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() 积己 角菩");

	cout << "家南 积己 己傍!" << endl;

	closesocket(hSocket);
	WSACleanup();
	return 0;
}