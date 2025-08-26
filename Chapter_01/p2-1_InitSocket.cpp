/*	
	윈속을 초기화하고 종료하는 간단한 콘솔 응용 프로그램을 작성해보자.
	InitSocket 프로젝트를 만들고 다음 코드를 입력한다.
*/

#include "Common.h"
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		err_quit("[오류] : 윈속 초기화 실패");
		return 1;
	}
	printf("[알림] 윈속 초기화 성공\n");

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
	printf("[알림] : 소켓 생성 성공 \n");

	// 소켓 닫기
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}