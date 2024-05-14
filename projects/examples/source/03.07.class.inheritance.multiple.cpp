#include <iostream>

//  ================================================================================================

class B { public: static inline auto m_data_1 = 42; int m_data_2 = 42; };

//  ================================================================================================

class L1 : public         B {}; 
class L2 : public virtual B {}; 

class R1 : public         B {}; 
class R2 : public virtual B {}; 

//  ================================================================================================

class C1 : public L1, public R1 {};
class C2 : public L2, public R2 {};

//  ================================================================================================

int main()
{
	C1 c1;

	std::cout << c1.m_data_1 << std::endl;
//	std::cout << c1.m_data_2 << std::endl; // error

	C2 c2;

	std::cout << c2.m_data_1 << std::endl;
	std::cout << c2.m_data_2 << std::endl;

	return 0;
}