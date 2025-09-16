// std::thread와 std::mutex로 두 스레드가 카운터를 안전하게 증가시키는 예시

#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

void worker(int id)
{
	for (int i = 0; i < 10000; i++)
	{
		// 안전하게 공유자원 보호
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