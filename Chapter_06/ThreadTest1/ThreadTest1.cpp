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
	std::cout << "Running MyThread()" << GetCurrentTreadId() << pt->x << pt->y << pt->z << std::endl;
	return 0;
}

int main(int argc, char* argv[])
{

}