#include <any>
#include <iostream>
#include <typeinfo>

#include <boost/type_index.hpp>

class Shape // note: polymorphic base class with virtual destructor
{
public:

	virtual ~Shape() = default;

}; // class Shape 

class Polygon : public Shape {};
class Ellipse : public Shape {};

int main()
{
	Shape * s_ptr = new Polygon;

	[[maybe_unused]] auto p_ptr = dynamic_cast < Polygon * > (s_ptr); // note: avoid downcasting

	delete s_ptr;

	s_ptr = new Ellipse;

	auto e_ptr = dynamic_cast < Polygon * > (s_ptr); // note: dynamic_cast provides runtime checks 

	if (!e_ptr)
	{
		std::cout << "invalid dynamic cast" << std::endl;
	}

	delete s_ptr;

	auto x = 42;

	[[maybe_unused]] decltype (x)  v = x; // note: decltype -> double

	[[maybe_unused]] decltype((x)) r = x; // note: decltype -> double &

	const auto & rcx = x;

	[[maybe_unused]] auto           z1 = rcx; // note:          auto  ->       double
	[[maybe_unused]] decltype(auto) z2 = rcx; // note: decltype(auto) -> const double &

	std::cout << typeid(x).name() << std::endl;

	std::string s = "hello";

	std::cout << typeid(s).name() << std::endl; // note: not portable type name

	s_ptr = new Polygon;

	const auto & type_info = typeid(*s_ptr);

	std::cout << type_info.name() << std::endl; // note: dynamic type identification

	delete s_ptr;

	const auto & reference = Polygon();

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