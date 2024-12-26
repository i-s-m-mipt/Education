#include <cstddef>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Singleton
{
public:

    Singleton            (const Singleton &) = delete;

    Singleton & operator=(const Singleton &) = delete;

//  --------------------------------------------------

    static auto & instance() 
    { 
        static D d; 
		
		return d; 
    }

protected:

    Singleton() = default;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v1 : public Singleton < Entity_v1 > 
{
public:

	void test() const
	{
		std::cout << "Entity_v1::test\n";
	}

private:

    friend Singleton < Entity_v1 > ; 

//  --------------------------------------------
	
	Entity_v1() = default;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v2
{
public:

	void test() const
	{
		std::cout << "Entity_v2::test\n";
	}

private:

	friend Singleton < Entity_v2 > ;

//  -------------------------------------

	Entity_v2() = default; 
};

///////////////////////////////////////////////////////////////////////////////////////////////

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
			std::cerr << "Counter::initialize : invalid instance\n";
		}
	}

//  -----------------------------------

	static inline auto s_counter = 0uz;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct Entity_v3 : private Counter < Entity_v3 < T > , 5 > {};
template < typename T > struct Entity_v4 : private Counter < Entity_v4 < T > , 5 > {};

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Entity_v1::instance().test();

	Singleton < Entity_v2 > ::instance().test();

//  --------------------------------------------

	Entity_v3 < int > entity_v3_1;
	
	Entity_v3 < int > entity_v3_2(entity_v3_1);

	Entity_v4 < int > entity_v4;
}