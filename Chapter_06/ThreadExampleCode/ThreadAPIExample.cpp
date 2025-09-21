#include <Windows.h>
#include <iostream>
#include <cstdint>	

// 스레드 시작 함수(winAPI 스레드 함수 규약 따라야 함)
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	int id = static_cast<int>(reinterpret_cast<intptr_t>(lpParam));
	std::cout << "Thread " << id << " 시작" << std::endl;

	Sleep(1000); // 1초 대기(작업 시뮬레이션)

	std::cout << "Thread " << id << "끝" << std::endl;
	return static_cast<DWORD>(id); // 스레드 종료 코드 반환
}

int main()
{
	// 새 스레드 생성(id = 1 전달)
	HANDLE hThread = CreateThread(
		nullptr,						// 보안 속성(기본 nullptr)
		0,								// 스택 크기(기본)
		ThreadFunc,						// 실행할 함수
		reinterpret_cast<LPVOID>(1),	// 전달할 인자(여기선 숫자 1)
		0,								// 생성 후 바로 실행
		nullptr							// 스레드 ID (필요없으면 nullptr)
	);

	if (hThread == nullptr)
	{
		std::cerr << "CreateThread 실패 : " << GetLastError() << std::endl;
		return 1;
	}

	// 스레드가 끝날 때까지 대기
	WaitForSingleObject(hThread, INFINITE);

	// 스레드 종료 코드 확인
	DWORD exitCode = 0;
	GetExitCodeThread(hThread, &exitCode);
	std::cout << "스레드 종료 코드 : " << exitCode << std::endl;

	// 핸들 닫기(필수)
	CloseHandle(hThread);

	return 0;
}