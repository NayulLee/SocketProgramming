// std::thread�� std::mutex�� �� �����尡 ī���͸� �����ϰ� ������Ű�� ����

#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

void worker(int id)
{
	for (int i = 0; i < 10000; i++)
	{
		// �����ϰ� �����ڿ� ��ȣ
		std::lock_guard<std::mutex>lock(m);
		++counter;
	}
	std::cout << "worker" << id << " done\n";
}

int main()
{
	std::thread t1(worker, 1);
	std::thread t2(worker, 2);

	t1.join();
	t2.join();

	std::cout << "final counter = " << counter << std::endl;
	return 0;
}