#include <any>
#include <iostream>
#include <typeinfo>

#include <boost/type_index.hpp>

//  ================================================================================================

class System 
{
public:

	virtual ~System() = default;

	virtual void test() const = 0;

}; // class System 

//  ================================================================================================

class Server : public System { void test() const override {	std::clog << "Server::test\n"; } };
class Client : public System { void test() const override { std::clog << "Client::test\n"; } };

//  ================================================================================================

int main()
{
	const System * system = new const Server();

	[[maybe_unused]] const auto server_1 = dynamic_cast < const Server * > (system);

	delete system;

	system = new const Client();

	if (const auto server_2 = dynamic_cast < const Server * > (system); !server_2)
	{
		std::cout << "invalid dynamic cast\n"; 
	}

	delete system;

//  ================================================================================================

	auto x = 1;

	[[maybe_unused]] decltype( x )     y = x;
	[[maybe_unused]] decltype((x)) ref_x = x;

	const auto & ref_cx = x;

	[[maybe_unused]]          auto  z1 = ref_cx; 
	[[maybe_unused]] decltype(auto) z2 = ref_cx;

//  ================================================================================================

	std::cout << typeid(x).name() << std::endl;

	const std::string string = "aaaaa";

	std::cout << typeid(string).name() << std::endl;

	system = new const Server();

	const auto & type_info = typeid(*system);

	std::cout << type_info.name() << std::endl;

	delete system;

	const auto & reference = Server();

	std::cout << typeid(reference).name() << std::endl;

//  ================================================================================================

	using boost::typeindex::type_id_with_cvr;

	std::cout << type_id_with_cvr < decltype(reference) > ().pretty_name() << std::endl;

//  ================================================================================================

	if (std::any any = std::make_any < decltype(x) > (x); any.has_value())
	{
		std::cout << any.type().name() << " : ";
		
		if (any.type() == typeid(int))
		{
			std::cout << std::any_cast < int > (any) << std::endl;
		}
		else
		{
			std::cout << "unknown type\n";
		}
	}
	else 
	{
		any = 1.0;
	}

	return 0;
}