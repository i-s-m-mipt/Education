/////////////////////////////////////////////////

#include <print>
#include <string>

/////////////////////////////////////////////////

namespace library
{
	namespace detail
	{
		struct Entity {};
	}
}

/////////////////////////////////////////////////

namespace library::detail
{
	void test(Entity)
	{
		std::print("library::detail::test\n");
	}
}

/////////////////////////////////////////////////

// void test(library::detail::Entity)
// {
//     std::print("test\n");
// }

/////////////////////////////////////////////////

namespace library
{
	inline namespace v1
	{
		void test()
		{
			std::print("library::v1::test\n");
		}
	}

//  ------------------------------------------

	namespace v2
	{
		void test()
		{
			std::print("library::v2::test\n");
		}
	}
}

/////////////////////////////////////////////////

int main()
{
	::library::detail::Entity entity;

//  ---------------------------------------------

	test(entity);

//  ---------------------------------------------

    namespace alias = ::library::detail;

//  ---------------------------------------------

	alias::test(entity);

//  ---------------------------------------------

    library::v1::test();

    library::v2::test();

	library::    test();

//  ---------------------------------------------

//  using namespace std; // bad

	using namespace std::literals;

//  ---------------------------------------------

	auto string_1 = "aaaaa"s;

	auto string_2 = std::operator""s("aaaaa", 5);
}

/////////////////////////////////////////////////