#include <cmath>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

// =================================================================================================

class C { public: constexpr explicit C(int) {} };

// =================================================================================================

class A { public: ~A() { std::cout << "destructor" << std::endl; } };

class B {};

// =================================================================================================

[[nodiscard]] inline constexpr std::variant < std::monostate, int, double > handle(int x) noexcept
{
	if (x < 0) return std::monostate(); else if (x == 0) return x; else return std::sqrt(x);
}

// =================================================================================================

[[nodiscard]] inline std::optional < std::string > create(bool b) // note: optional returned value
{
	return (b ? std::optional < std::string > ("object") : std::nullopt);
}

// =================================================================================================

int main()
{
	std::variant < char, int, double > v1;

	v1 = 42; // note: now holding integer value

	std::get < int > (v1) += 42;

	if (const auto ptr = std::get_if < int > (&v1); ptr)
	{
		*ptr = 42;
	}

//	constexpr std::variant < C, int > v2; // error: not default constructible

	constexpr std::variant < std::monostate, C, int > v3;

	constexpr std::variant < char, int, double > v4(3.14); // note: double

	std::cout << std::get < double > (v4) << std::endl;

//	constexpr std::variant < char, double > v5(42); // error: ambiguous selection

	constexpr std::variant < char, double > v6(std::in_place_type < double > , 42);

	constexpr std::variant < char, double > v7(std::in_place_index < 1 > , 42);

	constexpr std::variant < int, int > v8(std::in_place_index < 0 > , 42);

	std::cout << v8.index() << std::endl;

	std::variant < A, B > v9;

	v9 = B(); // good: no memory leaks, destructor called

	if (constexpr auto result = handle(42); std::holds_alternative < double > (result))
	{
		std::cout << std::get < double > (result) << std::endl;
	}

	constexpr std::optional < int > o1; // note: same as std::nullopt

    std::cout << o1.has_value() << std::endl;

    auto o2 = std::make_optional(42);

    o2.reset(); // note: same as std::nullopt

    const std::optional < std::string > o3(std::in_place, 5, 'a'); // note: in-place construction

    std::cout << *o3 << ' ' << o3->front() << std::endl;

    std::cout << create(false).value_or("empty") << std::endl;

    if (const auto object = create(true); object)
    {
        std::cout << *object << std::endl;
    }

	return 0;
}