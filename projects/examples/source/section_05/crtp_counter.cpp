#include <iostream>

template < typename T, std::size_t M > class Counter 
{
protected:

	Counter(                         ) { initialize(); }
	Counter(const Counter < T, M > & ) { initialize(); }
	Counter(      Counter < T, M > &&) { initialize(); }

	void initialize() // good: better than singleton
	{
		if (++counter > M)
		{
			std::cout << "Error: too many objects" << std::endl;
		}
	}

	~Counter() { --counter; } // note: non-polymorphic class

public:

	[[nodiscard]] static auto get_counter() { return counter; }

private:

	static inline std::size_t counter = 0;

}; // template < typename T > class Counter

template < typename T >
class Container_1 : public Counter < Container_1 < T > , 1 > {};

template < typename T >
class Container_2 : public Counter < Container_2 < T > , 2 > {};

int main()
{
	Container_1 < int > ci_1;
	Container_1 < int > ci_2(ci_1); // note: second instance

	Container_2 < int > ci_3;

	std::cout << Container_1 < int > ::get_counter() << std::endl;
	std::cout << Container_2 < int > ::get_counter() << std::endl;

	return 0;
}