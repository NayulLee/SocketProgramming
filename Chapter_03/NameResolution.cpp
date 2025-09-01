#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define TESTNAME "www.google.com"
#include "../Chapter_01/Common.h"
#include <iostream>
#include <cstring>
#include <WS2tcpip.h>	// inet_ntop, AF_INET���� ����

#pragma comment(lib, "ws2_32.lib")

// ������ �̸��� IPv4�ּҷ� ��ȯ
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

// IPv4�ּҸ� �������̸�����
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

    std::cout << "������ �̸�(��ȯ ��) : " << TESTNAME << std::endl;

    // ������ �̸� > IP�ּ�
    struct in_addr addr;
    if (GetIPAddr(TESTNAME, &addr))
    {
        // �����̸� ��� ���
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &addr, str, sizeof(str));
        std::cout << "IP�ּ� (��ȯ ��) : " << str << std::endl;
    }

    // IP�ּ� > ������ �̸�
    char name[256];
    if (GetDomainName(addr, name, sizeof(name)))
    {
        // �����̸� ��� ���
        std::cout << "������ �̸�(�ٽ� ��ȯ ��) : " << name << std::endl;
    }

    WSACleanup();
    return 0;
}