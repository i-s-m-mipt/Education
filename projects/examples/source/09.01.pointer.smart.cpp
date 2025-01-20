#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/noncopyable.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class RAII : private boost::noncopyable
{
public:

	RAII(T data) : m_data(new T(data)) {}

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

/////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(std::shared_ptr < int > , int) {}

[[noreturn]] int test_v2() 
{
	throw std::runtime_error("error");
}

/////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////

class Router : public Entity 
{
public:

	void test() const override 
	{ 
		std::cout << "Router::test\n"; 
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		RAII < int > raii(1);
	}

//  -----------------------------------------------------------------------------

	{
		std::shared_ptr < int > shared_ptr_1;

		std::shared_ptr < int > shared_ptr_2(new auto(2)); 

		std::shared_ptr < int > shared_ptr_3(shared_ptr_2);

		assert(shared_ptr_2.use_count() == 2 && *shared_ptr_2 == 2);

		assert(shared_ptr_3.use_count() == 2 && *shared_ptr_3 == 2);

		shared_ptr_3.reset(new auto(3));

		assert(shared_ptr_2.use_count() == 1 && *shared_ptr_2 == 2);

		assert(shared_ptr_3.use_count() == 1 && *shared_ptr_3 == 3);
	}	

//  -----------------------------------------------------------------------------

	{
		auto object = new auto(1);

//		std::shared_ptr < int > shared_ptr(object); // bad

		delete object;
	}

//  -----------------------------------------------------------------------------

	{
//		test_v1(std::shared_ptr < int > (new auto(1)), test_v2()); // bad

		auto shared_ptr = std::make_shared < int > (1);

		try
		{
			test_v1(std::make_shared < int > (1), test_v2());
		}
		catch (...) {}
	}

//  -----------------------------------------------------------------------------

	{
//		std::shared_ptr < int > shared_ptr_1(new int[5]{ 1, 2, 3, 4, 5 }); // bad

		std::shared_ptr < int > shared_ptr_2
		(
			new int[5]{ 1, 2, 3, 4, 5 }, std::default_delete < int[] > ()
		);

//		assert(shared_ptr_2[0] == 1); // error

		std::shared_ptr < int[] > shared_ptr_3(new int[5]{ 1, 2, 3, 4, 5 });

		assert(shared_ptr_3[0] == 1);

//		assert(*shared_ptr_3 == 1 && *(shared_ptr_3 + 1) == 2); // error
	}

//  -----------------------------------------------------------------------------

	{
		auto shared_ptr = std::make_shared < int > (1);

		std::weak_ptr < int > weak_ptr = shared_ptr;

		assert(weak_ptr.use_count() == 1);

		*weak_ptr.lock() = 1;

		shared_ptr.reset();

		assert(weak_ptr.expired());
	}

//  -----------------------------------------------------------------------------

	{
		auto client         = std::make_shared < Client > (); 
		
		     client->server = std::make_shared < Server > ();

			 client->server->client = client;
	}

//  -----------------------------------------------------------------------------

	{
		auto unique_ptr_1 = std::make_unique < int > (1);

		auto unique_ptr_2 = std::move(unique_ptr_1);

		std::unique_ptr < Entity > unique_ptr_3 = std::make_unique < Router > ();

		unique_ptr_3->test();
	}
}