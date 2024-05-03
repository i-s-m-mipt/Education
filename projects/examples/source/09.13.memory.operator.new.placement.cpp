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

   ~U() {} // note: what should be destroyed here?

	std::string string_1;
	std::string string_2;

}; // union U

//  ================================================================================================

template < typename T > class Manager // note: non-polymorphic base class
{
protected:

	constexpr  Manager()          = default;
    constexpr ~Manager() noexcept = default;

public: // note: consider overloading of all other versions of new and delete

	[[nodiscard]] void * operator new(std::size_t size) // note: implicitly static
	{
		std::cout << "Manager::operator new called" << std::endl;

		return ::operator new(size); // note: global operator new call
	}

	void operator delete(void * pointer, std::size_t) // note: implicitly static
	{
		std::cout << "Manager::operator delete called" << std::endl;

		return ::operator delete(pointer); // note: global operator delete call
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

int main(int argc, char ** argv) // note: arguments for benchmark
{
	assert(sizeof(C) == sizeof(std::size_t));

	constexpr std::size_t size = 5;

	const auto ptr = static_cast < C * > (::operator new(sizeof(C) * size)); // note: uninitialized memory

	for (std::size_t i = 0; i < size; ++i)
	{
		new (ptr + i) C(i); // note: placement new, construction without allocation
	}

	constexpr std::size_t offset = size / 2;

	(ptr + offset)->~C(); // good: explicit element destructor call 

	new (ptr + offset) C(42); // note: object reconstruction in the same memory cell

	for (std::size_t i = 0; i < size; ++i)
	{
		ptr[i].~C();
	}

	::operator delete(ptr, sizeof(C) * size); // note: hint for memory allocator

//  ================================================================================================

	std::cout << sizeof(U) << std::endl;

	U u; // note: consider std::variant

	u.string_1 = "hello";

	u.string_1.~basic_string(); // good: explicit member destructor call

	new (&u.string_2) std::string;

	u.string_2 = "world";

	u.string_2.~basic_string(); // good: explicit member destructor call

//  ================================================================================================
	
	delete(new const User); // note: overloaded versions instead of global

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}
