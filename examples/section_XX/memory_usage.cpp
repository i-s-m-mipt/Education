import std;

void f(std::size_t size)
{
	auto a = new int[size]{}; // note: dynamic allocation

	for (std::size_t i = 0; i < size; ++i)
	{
		a[i] = static_cast < int > (i + 1);
	}

	std::this_thread::sleep_for(std::chrono::seconds(1)); // note: delay

	// delete[] a; // bad: memory leak
}

int main()
{
	f(5'000'000);
	f(5'000'000);
	f(5'000'000);
	f(5'000'000);
	f(5'000'000);

	return 0;
}