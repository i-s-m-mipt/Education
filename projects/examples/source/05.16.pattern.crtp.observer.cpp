#include <iostream>

//  ================================================================================================

template < typename T, std::size_t M > class Counter
{
protected:

	Counter(                         ) { initialize(); }
	Counter(const Counter < T, M > & ) { initialize(); }
	Counter(      Counter < T, M > &&) { initialize(); }

   ~Counter() { --counter; }

private:

	void initialize()
	{
		if (++counter > M)
		{
			std::cerr << "too many objects\n";
		}
	}

public:

	[[nodiscard]] static std::size_t get_counter() { return counter; }

private:

	static inline std::size_t counter = 0;

}; // template < typename T > class Counter

//  ================================================================================================

template < typename T > class Container_1 : private Counter < Container_1 < T > , 1 > 
{
public: using Counter < Container_1 < T > , 1 > ::get_counter;
};

//  ================================================================================================

template < typename T > class Container_2 : private Counter < Container_2 < T > , 2 > 
{
public: using Counter < Container_2 < T > , 2 > ::get_counter;
};

//  ================================================================================================

int main()
{
	const Container_1 < int > ci_1;
	
	const Container_1 < int > ci_2(ci_1);

	const Container_2 < int > ci_3;

	std::cout << Container_1 < int > ::get_counter() << std::endl;
	std::cout << Container_2 < int > ::get_counter() << std::endl;

	return 0;
}