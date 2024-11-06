#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <boost/noncopyable.hpp>

//  ================================================================================================

template < typename T > class RAII : private boost::noncopyable
{
public:

	explicit RAII(T data) : m_data(new T(data)) {}

   ~RAII() 
	{ 
		if (m_data) 
		{
			delete m_data; 
		}
	}

//  ------------------------------

	auto get() const
	{ 
		return m_data; 
	}

private:

	T * m_data = nullptr;
}; 

//  ================================================================================================

void test_v1(std::shared_ptr < int > , int) {}

[[noreturn]] int test_v2() 
{
	throw std::runtime_error("error");
}

//  ================================================================================================

struct Client
{
   ~Client() 
    { 
		std::clog << "Client::~Client\n";
	}

//  -----------------------------------------

	std::shared_ptr < struct Server > server;
};

//  ================================================================================================

struct Server
{
   ~Server() 
    { 
		std::clog << "Server::~Server\n";
	}

//  --------------------------------

	std::weak_ptr < Client > client;
};

//  ================================================================================================

struct Entity 
{
	virtual ~Entity() = default; 

//  -------------------------------------

	virtual void test() const
	{ 
		std::clog << "Base::Entity\n"; 
	}
};

//  ================================================================================================

struct Router : public Entity 
{
	void test() const override 
	{ 
		std::cout << "Router::test\n"; 
	}
}; 

//  ================================================================================================

template < typename E > auto make_entity()
{
	return std::unique_ptr < Entity > (std::make_unique < E > ());
}

void test_v3(std::unique_ptr < Entity > entity)
{
	entity->test();
}

//  ================================================================================================

int main()
{
	{
		RAII < int > raii(1);
	}

//  -------------------------------------

	std::shared_ptr < int > shared_ptr_1;

	if (shared_ptr_1)
	{
		std::cout << shared_ptr_1 << std::endl;
	}

	std::shared_ptr < int > shared_ptr_2(new auto(1)); 

	std::shared_ptr < int > shared_ptr_3(shared_ptr_2);

	assert(shared_ptr_2.use_count() == 2 && *shared_ptr_2 == 42);
	assert(shared_ptr_3.use_count() == 2 && *shared_ptr_3 == 42);

	shared_ptr_3.reset(new auto(1));

	assert(shared_ptr_2.use_count() == 1 && *shared_ptr_2 == 42);
	assert(shared_ptr_3.use_count() == 1 && *shared_ptr_3 == 42);

//  ================================================================================================

	auto object = new auto(1);

//	std::shared_ptr < int > shared_ptr_4(object); // bad

	delete object;

//  ================================================================================================

//	test_v1(std::shared_ptr < int > (new auto(1)), test_v2()); // bad

	auto shared_ptr_5 = std::make_shared < int > (1);

	try
	{
		test_v1(std::make_shared < int > (1), test_v2());
	}
	catch (...) {}

//  ================================================================================================

	auto size = 5uz;

//	std::shared_ptr < int > shared_ptr_6(new int[size]{}); // bad

	std::shared_ptr < int > shared_ptr_7(new int[size]{}, std::default_delete < int[] > ());

//	*(shared_ptr_7++) = 42; // error

	auto shared_ptr_8 = std::make_shared < int[] > (size, 0);

	shared_ptr_8[0] = 42;

//  ================================================================================================

	auto shared_ptr_9 = std::make_shared < int > (42);

	std::weak_ptr < int > weak_ptr = shared_ptr_9;

	assert(weak_ptr.use_count() == 1);

	*weak_ptr.lock() = 42;

	shared_ptr_9.reset();

	assert(weak_ptr.expired());

//  ================================================================================================

	{
		auto client         = std::make_shared < Client > (); 
		     client->server = std::make_shared < Server > ();

		client->server->client = client;
	}

//  ================================================================================================

	auto unique_ptr_1 = std::make_unique < int > (1);

	auto unique_ptr_2 = std::move(unique_ptr_1);

	auto unique_ptr_3 = make_entity < Router > (); 

	test_v3(std::move(unique_ptr_3));
}