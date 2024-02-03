#include <any>
#include <iostream>
#include <typeinfo>

#include <boost/type_index.hpp>

class Computer
{
public:

	virtual ~Computer() = default; // note: polymorphic base class

	virtual void run() const = 0;

}; // class Computer 

struct Mobile : public Computer { void run() const override { std::cout << "Mobile" << std::endl; } };
struct Tablet : public Computer { void run() const override { std::cout << "Tablet" << std::endl; } };
struct Laptop : public Computer { void run() const override { std::cout << "Laptop" << std::endl; } };

int main()
{
	Computer * c_ptr = new Mobile;

	[[maybe_unused]] auto m_ptr = dynamic_cast < Mobile * > (c_ptr); // note: avoid downcasting

	delete c_ptr;

	c_ptr = new Tablet;

	if (auto t_ptr = dynamic_cast <Mobile*> (c_ptr); !t_ptr) // note: dynamic_cast provides runtime checks 
	{
		std::cout << "invalid dynamic cast" << std::endl;
	}

	delete c_ptr;

	auto x = 42;

	[[maybe_unused]] decltype (x)  v = x; // note: decltype -> double

	[[maybe_unused]] decltype((x)) r = x; // note: decltype -> double &

	const auto & rcx = x;

	[[maybe_unused]] auto           z1 = rcx; // note:          auto  ->       double
	[[maybe_unused]] decltype(auto) z2 = rcx; // note: decltype(auto) -> const double &

	std::cout << typeid(x).name() << std::endl;

	std::string s = "hello";

	std::cout << typeid(s).name() << std::endl; // note: not portable type name

	c_ptr = new Mobile;

	const auto & type_info = typeid(*c_ptr);

	std::cout << type_info.name() << std::endl; // note: dynamic type identification

	delete c_ptr;

	const auto & reference = Mobile();

	std::cout << typeid(reference).name() << std::endl; // note: typeid provides not reliable result

	std::cout << boost::typeindex::type_id_with_cvr < decltype(reference) > ().pretty_name() << std::endl;

	if (auto any = std::make_any < decltype(x) > (x); any.has_value()) // note: any with int value
	{
		std::cout << any.type().name() << ": " << std::any_cast < int > (any) << std::endl;
	}
	else
	{
		any = 3.14; // note: Python is watching you...
	}

	return 0;
}