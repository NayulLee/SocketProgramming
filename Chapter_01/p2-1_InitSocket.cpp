/*	
	������ �ʱ�ȭ�ϰ� �����ϴ� ������ �ܼ� ���� ���α׷��� �ۼ��غ���.
	InitSocket ������Ʈ�� ����� ���� �ڵ带 �Է��Ѵ�.
*/

#include "Common.h"
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;
	printf("[�˸�] ���� �ʱ�ȭ ����\n");

	// ���� ����
	WSACleanup();
	return 0;
}