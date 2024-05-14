#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <boost/noncopyable.hpp>

//  ================================================================================================

template < typename T > class Resource : private boost::noncopyable
{
public:

	constexpr explicit Resource(T value) : m_ptr(new T(value)) {}

	constexpr ~Resource() noexcept { if (m_ptr) delete m_ptr; }

	[[nodiscard]] constexpr T * get() const noexcept { return m_ptr; }

private:

	T * const m_ptr;

}; // template < typename T > class Resource : private boost::noncopyable 

//  ================================================================================================

inline void f(std::shared_ptr < const int > , int) noexcept {}

[[nodiscard]] inline constexpr int bad(bool make_error = true) 
{
	if (make_error) throw std::runtime_error("error");

	return 0;
}

//  ================================================================================================

class B;

class A
{
public:

   ~A() noexcept { try { std::cout << "A destroyed" << std::endl; } catch (...) {} }

	std::shared_ptr < B > b;

}; // class A

//  ================================================================================================

class B
{
public:

   ~B() noexcept { try { std::cout << "B destroyed" << std::endl; } catch (...) {} }

//  std::shared_ptr < A > bad_a; // bad

	std::weak_ptr < A > a;

}; // class B

//  ================================================================================================

class Base 
{
public:

	virtual ~Base() noexcept = default; 

	virtual void print() const { std::cout << "Base" << std::endl; }

}; // class Base 

//  ================================================================================================

class Derived : public Base 
{
public: void print() const override { std::cout << "Derived" << std::endl; }
}; 

//  ================================================================================================

[[nodiscard]] inline std::unique_ptr < const Base > produce()
{
	return std::make_unique < const Derived > ();
}

inline void consume(std::unique_ptr < const Base > base)
{
	base->print();
}

//  ================================================================================================

int main()
{
	try
	{
		const Resource < int > resource(42);

		throw std::runtime_error("error");
	}
	catch (...) {}

//  ================================================================================================

	const std::shared_ptr < const int > shared_ptr_1;

	if (shared_ptr_1)
	{
		std::cout << shared_ptr_1 << std::endl;
	}

	std::shared_ptr < const int > shared_ptr_2(new const auto(42)); 

	std::shared_ptr < const int > shared_ptr_3(shared_ptr_2);

	assert(shared_ptr_2.use_count() == 2 && *shared_ptr_2 == 42);
	assert(shared_ptr_3.use_count() == 2 && *shared_ptr_3 == 42);

	shared_ptr_3.reset(new const auto(42));

	assert(shared_ptr_2.use_count() == 1 && *shared_ptr_2 == 42);
	assert(shared_ptr_3.use_count() == 1 && *shared_ptr_3 == 42);

//  ================================================================================================

	const auto ptr = new const auto(42);

//	const std::shared_ptr < const int > shared_ptr_4(ptr); // bad

	delete ptr;

//  ================================================================================================

//	f(std::shared_ptr < const int > (new const auto(42)), bad()); // bad

	const auto shared_ptr_5 = std::make_shared < const int > (42);

	try
	{
		f(std::make_shared < const int > (42), bad());
	}
	catch (...) {}

//  ================================================================================================

	constexpr std::size_t size = 5;

//	const std::shared_ptr < int > shared_ptr_6(new int[size]{}); // bad

	std::shared_ptr < int > shared_ptr_7(new int[size]{}, std::default_delete < int[] > ());

//	*(shared_ptr_7++) = 42; // error

	const auto shared_ptr_8 = std::make_shared < int[] > (size, 0); // support: std::array

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
		const auto a    = std::make_shared < A > (); 
		           a->b = std::make_shared < B > ();

		a->b->a = a;
	}

//  ================================================================================================

	auto unique_pointer_1 = std::make_unique < const int > (42);

	auto unique_pointer_2 = std::move(unique_pointer_1);

	auto unique_pointer_3 = produce(); 

	consume(std::move(unique_pointer_3));

	return 0;
}