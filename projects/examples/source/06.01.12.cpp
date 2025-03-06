#include <iostream>

/////////////////////////////////////////////////////////

namespace library
{
	namespace detail
	{
		struct Entity {};
	}
}

/////////////////////////////////////////////////////////

namespace library::detail
{
	void test(Entity)
	{
		std::cout << "library::detail::test\n";
	}
}

/////////////////////////////////////////////////////////

namespace library
{
	inline namespace v1
	{
		void test()
		{
			std::cout << "library::v1::test\n";
		}
	}

	namespace v2
	{
		void test()
		{
			std::cout << "library::v2::test\n";
		}
	}
}

/////////////////////////////////////////////////////////

int main()
{
    ::library::detail::test(::library::detail::Entity());

//  -----------------------------------------------------

    namespace alias = library::detail;

//  -----------------------------------------------------

	alias::test(alias::Entity());

           test(alias::Entity());

//  -----------------------------------------------------

    library::v1::test();

    library::v2::test();

	library::    test();

//  -----------------------------------------------------

//  using namespace std; // bad

	using namespace std::literals;

//  -----------------------------------------------------

	auto string_1 = "aaaaa"s;

	auto string_2 = std::operator""s("aaaaa", 5);
}