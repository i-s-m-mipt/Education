#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

std::mutex        mutex;
std::queue< int > queue;

std::condition_variable condition_variable;

void prepare()
{
	std::lock_guard<std::mutex> lock(mutex);
	queue.push(42);
	condition_variable.notify_one(); // notify_all
}

void process()
{
	std::unique_lock < std::mutex > lock(mutex);
	condition_variable.wait(lock, [] { return !queue.empty(); }); // ложное пробуждение
	int data = queue.front();
	queue.pop();
	lock.unlock();
	// ...
}

int main(int argc, char ** argv)
{
	std::thread t1(prepare);
	std::thread t2(process);

	t1.join();
	t2.join();

	system("pause");

	return EXIT_SUCCESS;
}
