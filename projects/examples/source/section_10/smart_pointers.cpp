#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <boost/noncopyable.hpp>

template < typename T > class Resource : private boost::noncopyable // good: RAII idiom
{
public:

	constexpr explicit Resource(T value) : m_ptr(new T(value)) {}

	[[nodiscard]] constexpr T * get() const noexcept { return m_ptr; }

	constexpr ~Resource() noexcept { if (m_ptr) delete m_ptr; } // good: no memory leak

private:

	T * const m_ptr; // note: copying is prohibited for example

}; // template < typename T > class Resource : private boost::noncopyable 

inline void f(std::shared_ptr < const int > , int) noexcept {}

[[nodiscard]] inline int bad(bool make_error = true) 
{
	if (make_error) throw std::runtime_error("error");

	return 0;
}

class B; // note: forward declaration as for plain pointers

class A
{
public:

	~A() noexcept { try { std::cout << "A destroyed" << std::endl; } catch (...) {} }

	std::shared_ptr < B > b;

}; // class A

class B
{
public:

	~B() noexcept { try { std::cout << "B destroyed" << std::endl; } catch (...) {} }

	std::weak_ptr < A > a; // note: immortal connection if shared_ptr

}; // class B

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

[[nodiscard]] inline std::unique_ptr < const Base > produce() // note: factory
{
	return std::make_unique < const Derived > ();
}

inline void consume(std::unique_ptr < const Base > base) // note: user
{
	base->print();
}

int main()
{
	try
	{
		const Resource < int > r(42); // note: destructor will be called

		throw std::runtime_error("error");
	}
	catch (...) {}

	const std::shared_ptr < const int > sptr_1; // note: same as nullptr

	if (sptr_1) // note: check if not nullptr as for plain pointer
	{
		std::cout << sptr_1 << std::endl;
	}

	std::shared_ptr < const int > sptr_2(new int(42)); // note: two new calls instead of one

	std::shared_ptr < const int > sptr_3(sptr_2);

	assert(sptr_2.use_count() == 2 && *sptr_2 == 42);
	assert(sptr_3.use_count() == 2 && *sptr_3 == 42);

	sptr_3.reset(new int(43));

	assert(sptr_2.use_count() == 1 && *sptr_2 == 42);
	assert(sptr_3.use_count() == 1 && *sptr_3 == 43);

	const int * const ptr = new int(42);

//	const std::shared_ptr < const int > sptr_4(ptr); // bad: don't mix with plain pointers

	delete ptr;

//	f(std::shared_ptr < const int > (new int(42)), bad()); // bad: possible memory leak

	const auto sptr_5 = std::make_shared < const int > (42); // good: one new call instead of two

	try
	{
		f(std::make_shared < const int > (42), bad()); // good: memory leak impossible
	}
	catch (...) {}

	constexpr std::size_t size = 10;

//	const std::shared_ptr < const int > sptr_6(new int[size]{}); // bad: undefined behavior

	std::shared_ptr < int > sptr_7(new int[size]{}, std::default_delete < int[] > ());

//	*(sptr_7++) = 42; // note: pointer arithmetic is prohibited, prefer iterators

	const auto sptr_8 = std::make_shared < int[] > (size, 0); // note: is it useful?

	sptr_8[0] = 42; // note: allowed only for array types

	auto sptr_9 = std::make_shared < int > (42);

	std::weak_ptr < int > wptr = sptr_9; // note: weak_ptr doesn't own object

	assert(wptr.use_count() == 1);

	*wptr.lock() = 43; // note: create shared_ptr from weak_ptr

	sptr_9.reset();

	assert(wptr.expired());

	{
		const auto a    = std::make_shared < A > (); 
		           a->b = std::make_shared < B > ();

		a->b->a = a; // note: cyclic dependency, destroy correctly
	}

	auto uptr_1 = std::make_unique < const int > (42); // note: much similar to shared_ptr

	auto uptr_2 = std::move(uptr_1); // note: move-only type

	auto uptr_3 = produce(); 

	consume(std::move(uptr_3)); // note: modern runtime polymorphism with factory

	return 0;
}