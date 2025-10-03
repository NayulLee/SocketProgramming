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
		// 스레드가 일시정지 상태로 생성, ResumeThread() 호출할 때까지 일시정지상태다.

	std::cout << "스레드 실행 전, 계산 결과" << sum << std::endl;

	ResumeThread(hThread); // 일시적정지 상태였던 스레드를 실제로 실행시킨다.
	WaitForSingleObject(hThread, INFINITE); // 스레드가 끝날 때까지 계속 기다린다.

	std::cout << "스레드 실행 후, 계산 결과" << sum << std::endl;

	CloseHandle(hThread);
	return 0;
	
}