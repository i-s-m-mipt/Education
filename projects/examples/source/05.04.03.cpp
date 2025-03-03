#include <iostream>

//////////////////////////////////////////////////////

template < typename D > class Singleton
{
public:

    Singleton            (const Singleton &) = delete;

    Singleton & operator=(const Singleton &) = delete;

//  --------------------------------------------------

    static auto & get() 
    { 
        static D d;
		
		return d;
    }

protected:

    Singleton() = default;
};

//////////////////////////////////////////////////////

class Entity_v1 : public Singleton < Entity_v1 > 
{
public:

	void test() const
	{
		std::cout << "Entity_v1::test\n";
	}

private:

    friend Singleton < Entity_v1 > ;

//  -------------------------------------
	
	Entity_v1() = default;
};

//////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////

int main()
{
	Entity_v1::get().test();

//  ---------------------------------------

	Singleton < Entity_v2 > ::get().test();
}