#include <iostream>

template < typename T > class Resource // good: RAII idiom
{
public:

	explicit Resource(T value) : m_ptr(new T(value)) {}

	Resource            (const Resource &) = delete;
	Resource & operator=(const Resource &) = delete;

	auto get() const noexcept { return m_ptr; }

	~Resource() noexcept { delete m_ptr; } // good: no memory leak

private:

	T * m_ptr; // note: copying is prohibited for example

}; // template < typename T > class Resource

int main()
{
	try
	{
		Resource < int > r(42); // note: destructor will be called

		throw std::runtime_error("error");
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
	}

	return 0;
}