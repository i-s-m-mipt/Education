#include <mutex>

int main(int argc, char ** argv)
{
	std::mutex mutex_A;
	std::mutex mutex_B;

	std::lock(mutex_A, mutex_B);

	std::lock_guard < std::mutex > lock_a(mutex_A, std::adopt_lock);
	std::lock_guard < std::mutex > lock_b(mutex_B, std::adopt_lock);

	// ...

	system("pause");

	return EXIT_SUCCESS;
}
