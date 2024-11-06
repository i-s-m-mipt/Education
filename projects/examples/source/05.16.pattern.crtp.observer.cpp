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
		std::clog << "Counter::initialize : s_counter = " << ++s_counter << " / " << S << '\n';
	}

//  -------------------------------------------------------------------------------------------

	static inline auto s_counter = 0uz;
};

//  ================================================================================================

template < typename T > struct Entity_v1 : private Counter < Entity_v1 < T > , 5 > {};
template < typename T > struct Entity_v2 : private Counter < Entity_v2 < T > , 5 > {};

//  ================================================================================================

int main()
{
	Entity_v1 < int > entity_v1_1;
	
	Entity_v1 < int > entity_v1_2(entity_v1_1);

	Entity_v2 < int > entity_v2;
}