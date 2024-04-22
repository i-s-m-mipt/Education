#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <boost/noncopyable.hpp>

// =================================================================================================

template < typename T > class Resource : private boost::noncopyable // good: RAII idiom
{
public:

	constexpr explicit Resource(T value) : m_ptr(new T(value)) {}

	constexpr ~Resource() noexcept { if (m_ptr) delete m_ptr; } // good: no memory leak

	[[nodiscard]] constexpr T * get() const noexcept { return m_ptr; }

private:

	T * const m_ptr; // note: copying is prohibited for example

}; // template < typename T > class Resource : private boost::noncopyable 

// =================================================================================================

inline void f(std::shared_ptr < const int > , int) noexcept {}

[[nodiscard]] inline int bad(bool make_error = true) 
{
	if (make_error) throw std::runtime_error("error");

	return 0;
}

// =================================================================================================

class B; // note: forward declaration as for plain pointers

class A
{
public:

   ~A() noexcept { try { std::cout << "A destroyed" << std::endl; } catch (...) {} }

	std::shared_ptr < B > b;

}; // class A

// =================================================================================================

class B
{
public:

   ~B() noexcept { try { std::cout << "B destroyed" << std::endl; } catch (...) {} }

	std::weak_ptr < A > a; // note: immortal connection if shared_ptr

}; // class B

// =================================================================================================

class Base 
{
public:

	virtual ~Base() noexcept = default; // note: polymorphic base class

	virtual void print() const { std::cout << "Base" << std::endl; }

}; // class Base 

// =================================================================================================

class Derived : public Base 
{
public:
	
	void print() const override { std::cout << "Derived" << std::endl; }

}; // class Derived : public Base 

// =================================================================================================

[[nodiscard]] inline std::unique_ptr < const Base > produce() // note: factory
{
	return std::make_unique < const Derived > ();
}

inline void consume(std::unique_ptr < const Base > base) // note: user
{
	base->print();
}

// =================================================================================================

int main()
{
	try
	{
		const Resource < int > resource(42); // note: destructor will be called

		throw std::runtime_error("error");
	}
	catch (...) {}

	const std::shared_ptr < const int > shared_ptr_1; // note: same as nullptr

	if (shared_ptr_1) // note: check if not nullptr as for plain pointer
	{
		std::cout << shared_ptr_1 << std::endl;
	}

	std::shared_ptr < const int > shared_ptr_2(new const int(42)); // note: two new calls instead of one

	std::shared_ptr < const int > shared_ptr_3(shared_ptr_2);

	assert(shared_ptr_2.use_count() == 2 && *shared_ptr_2 == 42);
	assert(shared_ptr_3.use_count() == 2 && *shared_ptr_3 == 42);

	shared_ptr_3.reset(new const int(42));

	assert(shared_ptr_2.use_count() == 1 && *shared_ptr_2 == 42);
	assert(shared_ptr_3.use_count() == 1 && *shared_ptr_3 == 42);

	const auto ptr = new const int(42);

//	const std::shared_ptr < const int > shared_ptr_4(ptr); // bad: don't mix with plain pointers

	delete ptr;

//	f(std::shared_ptr < const int > (new const int(42)), bad()); // bad: possible memory leak

	const auto shared_ptr_5 = std::make_shared < const int > (42); // good: one new call instead of two

	try
	{
		f(std::make_shared < const int > (42), bad()); // good: memory leak impossible
	}
	catch (...) {}

	constexpr std::size_t size = 5;

//	const std::shared_ptr < const int > shared_ptr_6(new const int[size]{}); // bad: undefined behavior

	std::shared_ptr < int > shared_ptr_7(new int[size]{}, std::default_delete < int[] > ());

//	*(shared_ptr_7++) = 42; // note: pointer arithmetic is prohibited, prefer iterators

	const auto shared_ptr_8 = std::make_shared < int[] > (size, 0); // note: is it useful?

	shared_ptr_8[0] = 42; // note: allowed only for array types

	auto shared_ptr_9 = std::make_shared < int > (42);

	std::weak_ptr < int > weak_ptr = shared_ptr_9; // note: weak_ptr doesn't own object

	assert(weak_ptr.use_count() == 1);

	*weak_ptr.lock() = 42; // note: create shared_ptr from weak_ptr

	shared_ptr_9.reset();

	assert(weak_ptr.expired());

	{
		const auto a    = std::make_shared < A > (); 
		           a->b = std::make_shared < B > ();

		a->b->a = a; // note: cyclic dependency, destroy correctly
	}

	auto unique_pointer_1 = std::make_unique < const int > (42); // note: much similar to shared_ptr

	auto unique_pointer_2 = std::move(unique_pointer_1); // note: move-only type

	auto unique_pointer_3 = produce(); 

	consume(std::move(unique_pointer_3)); // note: modern runtime polymorphism with factory

	return 0;
}