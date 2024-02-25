#include <cassert>
#include <iostream>
#include <new>
#include <string>

#include <benchmark/benchmark.h>

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

	std::size_t m_index;

}; // class C

union U
{
	U() : s1() {}

	~U() {} // note: what should be destroyed here?

	std::string s1;
	std::string s2;

}; // union U

template < typename T > class Manager // note: CRTP
{
public:

	void * operator new(std::size_t size) // note: overloaded version for Manager, implicitly static
	{
		std::cout << "Manager::operator new called" << std::endl;

		return ::operator new(size); // note: global operator new call
	}

	void operator delete(void * pointer, std::size_t size) // note: overloaded version for Manager, implicitly static
	{
		std::cout << "Manager::operator delete called" << std::endl;

		return ::operator delete(pointer); // note: global operator delete call
	}

}; // template < typename T > class Manager

class User : public Manager < User >
{
public:

	User()
	{
		std::cout << "User:: User called" << std::endl;
	}

	~User()
	{
		std::cout << "User::~User called" << std::endl;
	}

}; // class User : public Manager < User > 

void test_1(benchmark::State & state)
{
    for (auto _ : state)
    {
		auto ptr = ::operator new(state.range(0));

		benchmark::DoNotOptimize(ptr);

		::operator delete(ptr);
    }
}

BENCHMARK(test_1)->RangeMultiplier(2)->Range(1024 * 1024, 1024 * 1024 * 1024);

int main(int argc, char ** argv) // note: arguments for benchmark
{
	assert(sizeof(C) == sizeof(std::size_t));

	const std::size_t size = 5;

	auto ptr = static_cast < C * > (::operator new(sizeof(C) * size)); // note: uninitialized memory

	for (std::size_t i = 0; i < size; ++i)
	{
		new (ptr + i) C(i); // note: placement new, construction without allocation
	}

	const std::size_t offset = size / 2;

	(ptr + offset)->~C();

	new (ptr + offset) C(42); // note: object reconstruction in the same memory cell

	for (std::size_t i = 0; i < size; ++i)
	{
		ptr[i].~C();
	}

	::operator delete(ptr); // note: uninitialized memory

	std::cout << sizeof(U) << std::endl;

	U u; // note: prefer using std::variant

	u.s1 = "hello";

	u.s1.~basic_string(); // good: explicit member destructor call

	new (&u.s2) std::string;

	u.s2 = "world";

	u.s2.~basic_string(); // good: explicit member destructor call

	delete(new User); // note: overloaded versions are used instead of global versions

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}
