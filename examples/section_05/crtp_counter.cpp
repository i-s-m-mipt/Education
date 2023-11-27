#include <iostream>

template < typename T > class Counter
{
protected:

	Counter()                                              { ++m_counter; }
	Counter([[maybe_unused]] const Counter < T > &  other) { ++m_counter; }
	Counter([[maybe_unused]]       Counter < T > && other) { ++m_counter; }

	~Counter() { --m_counter; }

public:

	static auto counter()
	{
		return m_counter;
	}

private:

	static inline std::size_t m_counter = 0;

}; // template < typename T > class Counter

template < typename T >
class Container_1 : public Counter < Container_1 < T > > {};

template < typename T >
class Container_2 : public Counter < Container_2 < T > > {};

int main()
{
	Container_1 < int > ci_1;
	Container_1 < int > ci_2(ci_1);

	Container_2 < int > ci_3;

	std::cout << Container_1 < int > ::counter() << std::endl;
	std::cout << Container_2 < int > ::counter() << std::endl;

	return 0;
}