#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define TESTNAME "www.google.com"
#include "../Chapter_01/Common.h"
#include <iostream>
#include <cstring>
#include <WS2tcpip.h>	// inet_ntop, AF_INET같은 정의

#pragma comment(lib, "ws2_32.lib")

// 도메인 이름을 IPv4주소로 변환
bool GetIPAddr(const char* name, struct in_addr* addr)
{
    struct hostent* ptr = gethostbyname(name);
    if (ptr == NULL)
    {
        err_display("gethostbyname()");
        return false;
    }

    if (ptr->h_addrtype != AF_INET)
        return false;
    memcpy(addr, ptr->h_addr, ptr->h_length);
    return true;
}

// IPv4주소를 도메인이름으로
bool GetDomainName(struct in_addr addr, char* name, int namelen)
{
    struct hostent* ptr = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
    if (ptr == NULL)
    {
        err_display("gethostbyaddr()");
        return false;
    }
    if (ptr->h_addrtype != AF_INET)
        return false;
    strncpy(name, ptr->h_name, namelen);
    return true;
}

int main(int argc, char* argv[])
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    std::cout << "도메인 이름(변환 전) : " << TESTNAME << std::endl;

    // 도메인 이름 > IP주소
    struct in_addr addr;
    if (GetIPAddr(TESTNAME, &addr))
    {
        // 성공이면 결과 출력
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &addr, str, sizeof(str));
        std::cout << "IP주소 (변환 후) : " << str << std::endl;
    }

    // IP주소 > 도메인 이름
    char name[256];
    if (GetDomainName(addr, name, sizeof(name)))
    {
        // 성공이면 결과 출력
        std::cout << "도메인 이름(다시 변환 후) : " << name << std::endl;
    }

    WSACleanup();
    return 0;
}