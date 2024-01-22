#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

template < typename T > class Resource // good: RAII idiom
{
public:

	explicit Resource(T value) : m_ptr(new T(value)) {}

	Resource            (const Resource &) = delete;
	Resource & operator=(const Resource &) = delete;

	[[nodiscard]] auto get() const noexcept { return m_ptr; }

	~Resource() noexcept { delete m_ptr; } // good: no memory leak

private:

	T * m_ptr; // note: copying is prohibited for example

}; // template < typename T > class Resource 

void f(std::shared_ptr < int > x, [[maybe_unused]] int y) {}

int bad(bool make_error = true) 
{
	if (make_error)
	{
		throw std::runtime_error("error");
	}

	return 0;
}

struct B; // note: forward declaration as for plain pointers

struct A
{
	~A() { std::cout << "A destroyed" << std::endl; }

	std::shared_ptr < B > b;

}; // struct A

struct B
{
	~B() { std::cout << "B destroyed" << std::endl; }

	std::weak_ptr < A > a; // note: immortal connection if shared_ptr

}; // struct B

class Base 
{
public:

	virtual ~Base() noexcept = default; // note: polymorphic base class

	virtual void print() const { std::cout << "Base" << std::endl; }

}; // class Base 

class Derived : public Base 
{
public:

	void print() const override { std::cout << "Derived" << std::endl; }

}; // class Derived : public Base 

[[nodiscard]] std::unique_ptr < Base > produce() // note: factory
{
	return std::make_unique < Derived > ();
}

void consume(std::unique_ptr < Base > base) // note: user
{
	base->print();
}

int main()
{
	try
	{
		Resource < int > r(42); // note: destructor will be called

		throw std::runtime_error("error");
	}
	catch (...) {}

	std::shared_ptr < int > sptr_1; // note: same as nullptr

	if (sptr_1) // note: check if not nullptr as for plain pointer
	{
		std::cout << sptr_1 << std::endl;
	}

	std::shared_ptr < int > sptr_2(new int(42)); // note: two new calls instead of one

	std::shared_ptr < int > sptr_3(sptr_2);

	assert(sptr_2.use_count() == 2 && *sptr_2 == 42);
	assert(sptr_3.use_count() == 2 && *sptr_3 == 42);

	sptr_3.reset(new int(43));

	assert(sptr_2.use_count() == 1 && *sptr_2 == 42);
	assert(sptr_3.use_count() == 1 && *sptr_3 == 43);

	auto ptr = new int(42);

//	std::shared_ptr < int > sptr_4(ptr); // bad: don't mix with plain pointers

	delete ptr;

//	f(std::shared_ptr < int > (new int(42)), bad()); // bad: possible memory leak

	auto sptr_5 = std::make_shared < int > (42); // good: one new call instead of two

	try
	{
		f(std::make_shared < int > (42), bad()); // good: memory leak impossible
	}
	catch (...) {}

	const std::size_t size = 10;

//	std::shared_ptr < int > sptr_6(new int[size]{}); // bad: undefined behavior

	std::shared_ptr < int > sptr_7(new int[size]{}, std::default_delete < int[] > ());

//	*(sptr_7++) = 42; // note: pointer arithmetic is prohibited, prefer iterators

	auto sptr_8 = std::make_shared < int[] > (size, 0); // note: is it useful?

	sptr_8[0] = 42; // note: allowed only for array types

	auto sptr_9 = std::make_shared < int > (42);

	std::weak_ptr < int > wptr = sptr_9; // note: weak_ptr doesn't own object

	assert(wptr.use_count() == 1);

	*wptr.lock() = 43; // note: create shared_ptr from weak_ptr

	sptr_9.reset();

	assert(wptr.expired());

	{
		auto a = std::make_shared < A > (); 
		a->b   = std::make_shared < B > ();

		a->b->a = a; // note: cyclic dependency, destroy correctly
	}

	auto uptr_1 = std::make_unique < int > (42); // note: much similar to shared_ptr

	auto uptr_2 = std::move(uptr_1); // note: move-only type

	auto uptr_3 = produce(); 

	consume(std::move(uptr_3)); // note: modern runtime polymorphism with factory

	return 0;
}