#include <cassert>
#include <iostream>
#include <new>
#include <string>

#include <benchmark/benchmark.h>

//  ================================================================================================

class C
{
public:

	explicit C(std::size_t index) : m_index(index)
	{
		std::cout << "C:: C called, index: " << m_index << std::endl;
	}

   ~C()
	{
		std::cout << "C::~C called, index: " << m_index << std::endl;
	}

private:

	const std::size_t m_index;

}; // class C

//  ================================================================================================

union U
{
	U() : string_1() {}

   ~U() {}

	std::string string_1;
	std::string string_2;

}; // union U

//  ================================================================================================

template < typename T > class Manager
{
protected:

	constexpr  Manager()          = default;
    constexpr ~Manager() noexcept = default;

public:

	[[nodiscard]] void * operator new(std::size_t size) // detail: static
	{
		std::cout << "Manager::operator new called" << std::endl;

		return ::operator new(size);
	}

	void operator delete(void * pointer, std::size_t) // detail: static
	{
		std::cout << "Manager::operator delete called" << std::endl;

		return ::operator delete(pointer);
	}

}; // template < typename T > class Manager

//  ================================================================================================

class User : private Manager < User >
{
public:

	using Manager < User > ::operator new   ;
	using Manager < User > ::operator delete;

public:

	User() { std::cout << "User:: User called" << std::endl; }
   ~User() { std::cout << "User::~User called" << std::endl; }

}; // class User : private Manager < User > 

//  ================================================================================================

void test_1(benchmark::State & state)
{
    for (auto _ : state)
    {
		auto ptr = ::operator new   (     state.range(0)); benchmark::DoNotOptimize(ptr);
		           ::operator delete(ptr, state.range(0));
    }
}

//  ================================================================================================

BENCHMARK(test_1)->RangeMultiplier(2)->Range(1024 * 1024, 1024 * 1024 * 1024);

//  ================================================================================================

int main(int argc, char ** argv)
{
	assert(sizeof(C) == sizeof(std::size_t));

	constexpr std::size_t size = 5;

	const auto ptr = static_cast < C * > (::operator new(sizeof(C) * size));

	for (std::size_t i = 0; i < size; ++i)
	{
		new (ptr + i) C(i);
	}

	constexpr std::size_t offset = size / 2;

	(ptr + offset)->~C();

	new (ptr + offset) C(42);

	for (std::size_t i = 0; i < size; ++i)
	{
		ptr[i].~C();
	}

	::operator delete(ptr, sizeof(C) * size);

//  ================================================================================================

	std::cout << sizeof(U) << std::endl;

	U u; // support: std::variant

	u.string_1 = "hello";

	u.string_1.~basic_string();

	new (&u.string_2) std::string;

	u.string_2 = "world";

	u.string_2.~basic_string();

//  ================================================================================================
	
	delete(new const User);

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}
