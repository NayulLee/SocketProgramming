#include <Windows.h>
#include <iostream>

int sum = 0;

DWORD WINAPI MyThread(LPVOID arg)
{
	int num = (int)(long long)arg;
	for (int i = 1; i <= num; i++)
		sum += i;
	return 0;
}

int main(int argc, char* argv[])
{
	int num = 100;
	HANDLE hThread = CreateThread(
		NULL, 0, MyThread, (LPVOID)(long long)num, CREATE_SUSPENDED, NULL);
		// �����尡 �Ͻ����� ���·� ����, ResumeThread() ȣ���� ������ �Ͻ��������´�.

	std::cout << "������ ���� ��, ��� ���" << sum << std::endl;

	ResumeThread(hThread); // �Ͻ������� ���¿��� �����带 ������ �����Ų��.
	WaitForSingleObject(hThread, INFINITE); // �����尡 ���� ������ ��� ��ٸ���.

	std::cout << "������ ���� ��, ��� ���" << sum << std::endl;

	CloseHandle(hThread);
	return 0;
	
}