#include <iostream>

/////////////////////////////////////////////////////////////////

namespace education
{
	namespace examples
	{
		struct Entity {};
	}
}

/////////////////////////////////////////////////////////////////

namespace education::examples
{
	void test(Entity)
	{
		std::cout << "education::examples::test\n";
	}
}

/////////////////////////////////////////////////////////////////

namespace education
{
	inline namespace library_v1
	{
		void test()
		{
			std::cout << "education::library_v1::test\n";
		}
	}

	namespace library_v2
	{
		void test()
		{
			std::cout << "education::library_v2::test\n";
		}
	}
}

/////////////////////////////////////////////////////////////////

int main()
{
    ::education::examples::test(::education::examples::Entity());

//  -------------------------------------------------------------

    namespace ee = education::examples;

//  -------------------------------------------------------------

    ee::test(ee::Entity());

        test(ee::Entity());

//  -------------------------------------------------------------

    education::library_v1::test();

    education::library_v2::test();

//  -------------------------------------------------------------

    education::test();

//  -------------------------------------------------------------

//  using namespace std; // bad

	using namespace std::literals;

//  -------------------------------------------------------------

	auto string_1 = "aaaaa"s;

	auto string_2 = std::operator""s("aaaaa", 5);
}