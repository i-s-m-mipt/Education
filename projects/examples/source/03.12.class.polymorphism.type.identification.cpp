#include <any>
#include <iostream>
#include <typeinfo>

#include <boost/type_index.hpp>

//  ================================================================================================

class Computer 
{
public:

	virtual ~Computer() {};

	virtual void run() const = 0;

}; // class Computer 

//  ================================================================================================

class Mobile : public Computer { public: void run() const override; };
class Tablet : public Computer { public: void run() const override; };
class Laptop : public Computer { public: void run() const override; };

//  ================================================================================================

void Mobile::run() const { std::cout << "Mobile" << std::endl; }
void Tablet::run() const { std::cout << "Tablet" << std::endl; }
void Laptop::run() const { std::cout << "Laptop" << std::endl; }

//  ================================================================================================

int main()
{
	const Computer * computer_ptr = new const Mobile();

	[[maybe_unused]] const auto mobile_ptr_1 = dynamic_cast < const Mobile * > (computer_ptr);

	delete computer_ptr;

	computer_ptr = new const Tablet();

	if (const auto mobile_ptr_2 = dynamic_cast < const Mobile * > (computer_ptr); !mobile_ptr_2)
	{
		std::cout << "invalid dynamic cast" << std::endl; 
	}

	delete computer_ptr;

//  ================================================================================================

	auto x = 42;

	[[maybe_unused]] decltype (x)  v = x;
	[[maybe_unused]] decltype((x)) r = x;

	const auto & rcx = x;

	[[maybe_unused]]          auto  z1 = rcx; 
	[[maybe_unused]] decltype(auto) z2 = rcx;

//  ================================================================================================

	std::cout << typeid(x).name() << std::endl;

	const std::string string = "hello";

	std::cout << typeid(string).name() << std::endl;

	computer_ptr = new const Mobile();

	const auto & type_info = typeid(*computer_ptr);

	std::cout << type_info.name() << std::endl;

	delete computer_ptr;

	const auto & reference = Mobile();

	std::cout << typeid(reference).name() << std::endl;

//  ================================================================================================

	using boost::typeindex::type_id_with_cvr;

	std::cout << type_id_with_cvr < decltype(reference) > ().pretty_name() << std::endl;

//  ================================================================================================

	if (auto any = std::make_any < decltype(x) > (x); any.has_value())
	{
		std::cout << any.type().name() << ": ";
		
		if (any.type() == typeid(int))
		{
			std::cout << std::any_cast < int > (any) << std::endl;
		}
		else
		{
			std::cout << "unknown type" << std::endl;
		}
	}
	else any = 3.14; // support: динамическая типизация Python

	return 0;
}