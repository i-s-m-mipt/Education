#include <any>
#include <iostream>
#include <typeinfo>

#include <boost/type_index.hpp>

// =================================================================================================

class Computer 
{
public:

	virtual ~Computer() {}; // note: polymorphic base class

	virtual void run() const = 0;

}; // class Computer 

// =================================================================================================

class Mobile : public Computer { public: void run() const override { std::cout << "Mobile" << std::endl; } };
class Tablet : public Computer { public: void run() const override { std::cout << "Tablet" << std::endl; } };
class Laptop : public Computer { public: void run() const override { std::cout << "Laptop" << std::endl; } };

// =================================================================================================

int main()
{
	const Computer * computer_ptr = new const Mobile();

	[[maybe_unused]] const auto mobile_ptr_1 = dynamic_cast < const Mobile * > (computer_ptr);

	delete computer_ptr;

	computer_ptr = new const Tablet();

	if (const auto mobile_ptr_2 = dynamic_cast < const Mobile * > (computer_ptr); !mobile_ptr_2)
	{
		std::cout << "invalid dynamic cast" << std::endl; // note: dynamic_cast has runtime checks 
	}

	delete computer_ptr;

	auto x = 42;

	[[maybe_unused]] decltype (x)  v = x; // note: decltype (x)  -> double
	[[maybe_unused]] decltype((x)) r = x; // note: decltype((x)) -> double &

	const auto & rcx = x;

	[[maybe_unused]]          auto  z1 = rcx; // note:          auto  ->       double
	[[maybe_unused]] decltype(auto) z2 = rcx; // note: decltype(auto) -> const double &

	std::cout << typeid(x).name() << std::endl;

	const std::string string = "hello";

	std::cout << typeid(string).name() << std::endl; // note: not portable type name

	computer_ptr = new const Mobile();

	const auto & type_info = typeid(*computer_ptr);

	std::cout << type_info.name() << std::endl; // note: dynamic type identification

	delete computer_ptr;

	const auto & reference = Mobile();

	std::cout << typeid(reference).name() << std::endl; // note: typeid provides not reliable result

	std::cout << boost::typeindex::type_id_with_cvr < decltype(reference) > ().pretty_name() << std::endl;

	if (auto any = std::make_any < decltype(x) > (x); any.has_value()) // note: any with int value
	{
		std::cout << any.type().name() << ": " << std::any_cast < int > (any) << std::endl;
	}
	else any = 3.14; // note: Python is watching you...

	return 0;
}