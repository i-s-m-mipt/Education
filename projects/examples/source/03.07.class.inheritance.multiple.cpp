#include <iostream>

// =================================================================================================

class B
{
public:

	static inline auto m_data_1 = 0; // note: no problems here

public:

	int m_data_2 = 0; // note: possible problem with multiple inheritance

}; // class B

// =================================================================================================

class L : public /*virtual*/ B {}; // good: virtual inheritance
class R : public /*virtual*/ B {}; // good: virtual inheritance

class C : public L, public R {}; // note: possible diamond problem

// =================================================================================================

int main()
{
	C c;

	std::cout << c.m_data_1 << std::endl;

//	std::cout << c.m_data_2 << std::endl; // error: ambiguous data member selection

	return 0;
}