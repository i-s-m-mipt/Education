#include <mutex>

struct Data
{
	int value;

	void f() {}
};

class Wrapper
{
public:

	template < typename Function >
	void process(Function function)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		function(m_data);
	}

private:

	Data m_data;
	std::mutex m_mutex;
};

Data * unprotected;

int main(int argc, char ** argv)
{
	Wrapper wrapper;
	wrapper.process([](Data & data) { unprotected = &data; });

	unprotected->f(); // dangerous !

	system("pause");

	return EXIT_SUCCESS;
}
