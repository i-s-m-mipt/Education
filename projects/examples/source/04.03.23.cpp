#include <concepts>
#include <iostream>

////////////////////////////////////////////////////////////////////

template < typename T > void test_v1(T) requires std::integral < T >
{
	std::cout << "test_v1\n";
}

template < std::integral T > auto test_v2(T)
{
	std::cout << "test_v2\n";
}

void test_v3([[maybe_unused]] std::integral auto x)
{
	std::cout << "test_v3\n";
}

////////////////////////////////////////////////////////////////////

int main()
{
    test_v1(1);
    
    test_v2(1);

    test_v3(1);
}