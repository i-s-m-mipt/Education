#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/noncopyable.hpp>

//////////////////////////////////////////////////////////////////////////

template < typename T > class RAII : private boost::noncopyable
{
public:

	RAII(T x) : m_data(new T(x)) {}

   ~RAII() 
	{ 
		if (m_data) 
		{
			delete m_data; 
		}
	}

private:

	T * m_data = nullptr;
}; 

//////////////////////////////////////////////////////////////////////////

void test_v1(std::shared_ptr < int > , int) {}

//////////////////////////////////////////////////////////////////////////

[[noreturn]] int test_v2() 
{
	throw std::runtime_error("error");
}

//////////////////////////////////////////////////////////////////////////

class Client
{
public:

   ~Client() 
    { 
		std::cout << "Client::~Client\n";
	}

//  ----------------------------------------

	std::shared_ptr < class Server > server;
};

//////////////////////////////////////////////////////////////////////////

class Server
{
public:

   ~Server() 
    { 
		std::cout << "Server::~Server\n";
	}

//  --------------------------------------

	std::weak_ptr < class Client > client;
};

//////////////////////////////////////////////////////////////////////////

class Entity 
{
public:

	virtual ~Entity() = default; 

//  ----------------------------------

	virtual void test() const
	{ 
		std::cout << "Entity::test\n"; 
	}
};

//////////////////////////////////////////////////////////////////////////

class Router : public Entity 
{
public:

	void test() const override 
	{ 
		std::cout << "Router::test\n"; 
	}
};

//////////////////////////////////////////////////////////////////////////

int main()
{
	{
		RAII < int > raii(1);
	}

//  ----------------------------------------------------------------------

	{
		std::shared_ptr < int > ptr_1;

		std::shared_ptr < int > ptr_2(new auto(2)); 

		std::shared_ptr < int > ptr_3(ptr_2);

		assert(ptr_2.use_count() == 2 && *ptr_2 == 2);

		assert(ptr_3.use_count() == 2 && *ptr_3 == 2);

		ptr_3.reset(new auto(3));

		assert(ptr_2.use_count() == 1 && *ptr_2 == 2);

		assert(ptr_3.use_count() == 1 && *ptr_3 == 3);
	}	

//  ----------------------------------------------------------------------

	{
		auto ptr_1 = new auto(1);

//		std::shared_ptr < int > ptr_2(ptr_1); // bad

		delete ptr_1;
	}

//  ----------------------------------------------------------------------

	{
//		test_v1(std::shared_ptr < int > (new auto(1)), test_v2()); // bad

		auto ptr = std::make_shared < int > (1);

		try
		{
			test_v1(std::make_shared < int > (1), test_v2());
		}
		catch (...) {}
	}

//  ----------------------------------------------------------------------

	{
//		std::shared_ptr < int > ptr_1(new int[5]{ 1, 2, 3, 4, 5 }); // bad

		std::shared_ptr < int > ptr_2
		(
			new int[5]{ 1, 2, 3, 4, 5 }, std::default_delete < int[] > ()
		);

//		assert(ptr_2[0] == 1); // error

		std::shared_ptr < int[] > array(new int[5]{ 1, 2, 3, 4, 5 });

		assert(array[0] == 1);

//		assert(*array == 1 && *(array + 1) == 2); // error
	}

//  ----------------------------------------------------------------------

	{
		auto ptr_1 = std::make_shared < int > (1);

		std::weak_ptr < int > ptr_2 = ptr_1;

		assert(ptr_2.use_count() == 1 && *ptr_2.lock() == 1);

		ptr_1.reset(); assert(ptr_2.expired());
	}

//  ----------------------------------------------------------------------

	{
		auto client         = std::make_shared < Client > (); 
		
		     client->server = std::make_shared < Server > ();

			 client->server->client = client;
	}

//  ----------------------------------------------------------------------

	{
		auto ptr_1 = std::make_unique < int > (1);

		auto ptr_2 = std::move(ptr_1);

		std::unique_ptr < Entity > ptr_3 = std::make_unique < Router > ();

		ptr_3->test();
	}
}