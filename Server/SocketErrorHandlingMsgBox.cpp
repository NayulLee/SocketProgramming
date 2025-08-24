#include <iostream>
#include <winsock2.h>
#include <windows.h> // MessageBox, FormatMessage ��
#pragma comment(lib, "ws2_32.lib") // ���� ���̺귯�� ��ũ

using namespace std;

// �޽��� �ڽ��� ���� ǥ���ϰ� ���α׷� ����
void err_quit(const char* msg)
{
    LPVOID lpMsgBuf;
    DWORD dw = WSAGetLastError(); // ������ ���� ���� �ڵ� ��������

    // ���� �ڵ� �� ��� ���� �� �ִ� ���ڿ��� ��ȯ
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,
        NULL
    );

    // �޽��� �ڽ��� ǥ��
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, L"socket() ���� ����", MB_OK | MB_ICONERROR);

    // �޸� ����
    LocalFree(lpMsgBuf);

    exit(1); // ���α׷� ����
}

int main()
{
    WSADATA wsaData;
    SOCKET hSocket;

    // ���� �ʱ�ȭ
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        err_quit("WSAStartup() ����");

    // ���� ����
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET)
        err_quit("socket() ���� ����");

    cout << "���� ���� ����!" << endl;

    closesocket(hSocket);
    WSACleanup();
    return 0;
}
