#include <iostream>
#include <winsock2.h>
#include <windows.h> // MessageBox, FormatMessage 등
#pragma comment(lib, "ws2_32.lib") // 윈속 라이브러리 링크

using namespace std;

// 메시지 박스로 오류 표시하고 프로그램 종료
void err_quit(const char* msg)
{
    LPVOID lpMsgBuf;
    DWORD dw = WSAGetLastError(); // 마지막 소켓 오류 코드 가져오기

    // 오류 코드 → 사람 읽을 수 있는 문자열로 변환
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,
        NULL
    );

    // 메시지 박스로 표시
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, L"socket() 생성 실패", MB_OK | MB_ICONERROR);

    // 메모리 해제
    LocalFree(lpMsgBuf);

    exit(1); // 프로그램 종료
}

int main()
{
    WSADATA wsaData;
    SOCKET hSocket;

    // 윈속 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        err_quit("WSAStartup() 실패");

    // 소켓 생성
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET)
        err_quit("socket() 생성 실패");

    cout << "소켓 생성 성공!" << endl;

    closesocket(hSocket);
    WSACleanup();
    return 0;
}
