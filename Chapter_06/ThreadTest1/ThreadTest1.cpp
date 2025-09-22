#include <windows.h>
#include <iostream>

struct Point3D
{
	int x, y, z;
};

DWORD WINAPI MyThread(LPVOID arg)
{
	Sleep(1000);
	Point3D* pt = (Point3D*)arg;
	std::cout << "Running MyThread() " << GetCurrentThreadId() << ": " 
		<< pt->x <<", " << pt->y << ", " << pt->z << std::endl;
	return 0;
}

int main(int argc, char* argv[])
{
	// 첫 번째 스레드 생성
	Sleep(1000);
	Point3D pt1 = { 10, 20, 30 };
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, 0, NULL);
	if (hThread1 == NULL) return 1;
	CloseHandle(hThread1);

	// 두 번째 스레드 생성
	Point3D pt2 = { 40, 50, 60 };
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread, &pt2, 0, NULL);
	if (hThread2 == NULL) return 1;
	CloseHandle(hThread2);

	std::cout << "Running main() " << GetCurrentThreadId() << std::endl;
	Sleep(2000);
	
	return 0;
}