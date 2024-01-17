#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

[[nodiscard]] auto f() // note: different functions have same types
{
	static auto state = 0; // note: internal state, see reference arguments

	return (state++);
}

class C // note: different classes have different types
{
public:

	[[nodiscard]] auto operator()() const { return (m_state++); }

private:

	mutable int m_state = 0; // note: internal state, see logical constancy

}; // class C

int main()
{
	std::vector < int > v1({ 1, 4, 2, 5, 3 });

	std::sort(std::begin(v1), std::end(v1));                 // note: 1 2 3 4 5
	std::sort(std::begin(v1), std::end(v1), std::greater()); // note: 5 4 3 2 1

	const std::size_t size = 5;

	C c; // note: functional object with overloaded operator()

	std::vector < int > v2(size, 0); std::generate(std::begin(v2), std::end(v2), f);
	std::vector < int > v3(size, 0); std::generate(std::begin(v3), std::end(v3), c);

	for (std::size_t i = 0; i < size; ++i)
	{
		assert(v2[i] == static_cast < int > (i));
		assert(v3[i] == static_cast < int > (i));
	}

	std::transform(std::begin(v2), std::end(v2), std::begin(v2),                 std::negate());
	std::transform(std::begin(v2), std::end(v2), std::begin(v3), std::begin(v3), std::plus  ());

	for (std::size_t i = 0; i < size; ++i)
	{
		assert(v3[i] == 0);
	}

	return 0;
}