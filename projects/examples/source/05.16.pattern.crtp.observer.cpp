#include <iostream>

//  ================================================================================================

template < typename D, std::size_t S > class Counter
{
protected:

	Counter(                         ) { initialize(); }
	Counter(const Counter < D, S > & ) { initialize(); }
	Counter(      Counter < D, S > &&) { initialize(); }

   ~Counter() 
    { 
		--s_counter; 
	}

private:

	void initialize() const
	{
		if (++s_counter > S)
		{
			std::cerr << "Counter::initialize : too many objects\n";
		}
	}

public:

	[[nodiscard]] static auto counter() 
	{ 
		return s_counter; 
	}

private:

	static inline auto s_counter = 0uz;
};

//  ================================================================================================

template < typename T > struct Entity_v1 : private Counter < Entity_v1 < T > , 1 > 
{
	using Counter < Entity_v1 < T > , 1 > ::counter;
};

//  ================================================================================================

template < typename T > struct Entity_v2 : private Counter < Entity_v2 < T > , 2 > 
{
	using Counter < Entity_v2 < T > , 2 > ::counter;
};

//  ================================================================================================

int main()
{
	Entity_v1 < int > entity_v1_1;
	
	Entity_v1 < int > entity_v1_2(entity_v1_1);

	Entity_v2 < int > entity_v2;

	std::cout << Entity_v1 < int > ::counter() << std::endl;
	std::cout << Entity_v2 < int > ::counter() << std::endl;
}