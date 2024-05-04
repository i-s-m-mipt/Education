#include <mutex>

int main(int argc, char ** argv)
{
	std::mutex mutex_A;
	std::mutex mutex_B;

	std::unique_lock < std::mutex > lock_a(mutex_A, std::defer_lock);
	std::unique_lock < std::mutex > lock_b(mutex_B, std::defer_lock);

	std::lock(lock_a, lock_b);

	lock_a.unlock();

	// ...

	lock_a.lock();

	// ...

	lock_b.unlock();

	system("pause");

	return EXIT_SUCCESS;
}
