#include <cassert>
#include <cmath>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>

//  ================================================================================================

class C { public: constexpr explicit C(int) {} };

//  ================================================================================================

class A { public: ~A() { std::cout << "destructor" << std::endl; } };

class B {};

//  ================================================================================================

[[nodiscard]] inline constexpr std::variant < std::monostate, int, double > handle(int x) noexcept
{
	if (x < 0) return std::monostate(); else if (x == 0) return x; else return std::sqrt(x);
}

//  ================================================================================================

[[nodiscard]] inline std::optional < std::string > create(bool b)
{
	return (b ? std::optional < std::string > ("object") : std::nullopt);
}

//  ================================================================================================

int main()
{
	constexpr auto epsilon = 0.000001;

	std::variant < char, int, double > variant_1;

	variant_1 = 42;

	std::get < int > (variant_1) += 42;

	if (const auto ptr = std::get_if < int > (&variant_1); ptr)
	{
		*ptr = 42;
	}

//	constexpr std::variant < C, int > variant_2; // error

	constexpr std::variant < std::monostate, C, int > variant_3;

	constexpr std::variant < char, int, double > variant_4(3.14);

	assert(std::abs(std::get < double > (variant_4) - 3.14) < epsilon);

//	constexpr std::variant < char, double > variant_5(42); // error

	constexpr std::variant < char, double > variant_6(std::in_place_type < double > , 42);

	constexpr std::variant < char, double > variant_7(std::in_place_index < 1 > , 42);

	constexpr std::variant < int, int > variant_8(std::in_place_index < 0 > , 42);

	assert(variant_8.index() == 0);

	std::variant < A, B > variant_9;

	variant_9 = B();

	if (constexpr auto result = handle(42); std::holds_alternative < double > (result))
	{
		assert(std::abs(std::get < double > (result) - std::sqrt(42)) < epsilon);
	}

//  ================================================================================================

	constexpr std::optional < int > optional_1;

    assert(!optional_1.has_value());

    auto optional_2 = std::make_optional(42);

    optional_2.reset();

    const std::optional < std::string > optional_3(std::in_place, 5, 'a');

    assert(*optional_3 == "aaaaa");

    assert(create(false).value_or("empty") == "empty");

    if (const auto object = create(true); object)
    {
        assert(*object == "object");
    }

//  ================================================================================================

  	constexpr boost::logic::tribool tribool = boost::logic::indeterminate;

  	if (tribool || !tribool)
    {
		std::cout << "true or false" << std::endl;
	}
 	else
	{
		std::cout << "indeterminate" << std::endl;
	}

	return 0;
}