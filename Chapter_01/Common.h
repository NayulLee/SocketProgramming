#ifndef __COMMON_H__
#define __COMMON_H__

#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>  // exit()

#pragma comment(lib, "Ws2_32.lib")

// 소켓 에러 발생 시 프로그램 종료
inline void err_quit(const char* msg)
{
    LPVOID lpMsgBuf = nullptr;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&lpMsgBuf, 0, NULL);

    MessageBoxA(NULL, (LPCSTR)lpMsgBuf, msg, MB_ICONERROR);
    LocalFree(lpMsgBuf);
    exit(1);
}

// 소켓 에러 발생 시 단순 출력
inline void err_display(const char* msg)
{
    LPVOID lpMsgBuf = nullptr;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&lpMsgBuf, 0, NULL);

    printf("[%s] %s\n", msg, (char*)lpMsgBuf);
    LocalFree(lpMsgBuf);
}

#endif // __COMMON_H__
