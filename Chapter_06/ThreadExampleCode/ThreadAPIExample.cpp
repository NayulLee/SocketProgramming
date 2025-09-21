#include <Windows.h>
#include <iostream>
#include <cstdint>	

// ������ ���� �Լ�(winAPI ������ �Լ� �Ծ� ����� ��)
DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
	int id = static_cast<int>(reinterpret_cast<intptr_t>(lpParam));
	std::cout << "Thread " << id << " ����" << std::endl;

	Sleep(1000); // 1�� ���(�۾� �ùķ��̼�)

	std::cout << "Thread " << id << "��" << std::endl;
	return static_cast<DWORD>(id); // ������ ���� �ڵ� ��ȯ
}

int main()
{
	// �� ������ ����(id = 1 ����)
	HANDLE hThread = CreateThread(
		nullptr,						// ���� �Ӽ�(�⺻ nullptr)
		0,								// ���� ũ��(�⺻)
		ThreadFunc,						// ������ �Լ�
		reinterpret_cast<LPVOID>(1),	// ������ ����(���⼱ ���� 1)
		0,								// ���� �� �ٷ� ����
		nullptr							// ������ ID (�ʿ������ nullptr)
	);

	if (hThread == nullptr)
	{
		std::cerr << "CreateThread ���� : " << GetLastError() << std::endl;
		return 1;
	}

	// �����尡 ���� ������ ���
	WaitForSingleObject(hThread, INFINITE);

	// ������ ���� �ڵ� Ȯ��
	DWORD exitCode = 0;
	GetExitCodeThread(hThread, &exitCode);
	std::cout << "������ ���� �ڵ� : " << exitCode << std::endl;

	// �ڵ� �ݱ�(�ʼ�)
	CloseHandle(hThread);

	return 0;
}