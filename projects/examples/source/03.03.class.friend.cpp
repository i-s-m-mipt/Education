#include <iostream>

//  ================================================================================================

class B;

class A
{
public:

	friend inline void print([[maybe_unused]] const A & a);

	friend B;

private: 

	const int m_data = 42; 
	
}; // class A

//  ================================================================================================

class C
{
public:

	inline void print([[maybe_unused]] const A & a, 
					  [[maybe_unused]] const B & b) const;

private: 

	const int m_data = 42; 
	
}; // class C

//  ================================================================================================

class B
{
public:

	       inline void    print([[maybe_unused]] const A & a) const;
	friend inline void C::print([[maybe_unused]] const A & a, 
								[[maybe_unused]] const B & b) const;

private: 

	const int m_data = 42; 
	
}; // class B

//  ================================================================================================

inline void    print([[maybe_unused]] const A & a)       { std::cout << a.m_data << std::endl; }
inline void B::print([[maybe_unused]] const A & a) const { std::cout << a.m_data << std::endl; }
inline void C::print([[maybe_unused]] const A & a, 
					 [[maybe_unused]] const B & b) const 
{
//	std::cout << a.m_data << std::endl; // error
	std::cout << b.m_data << std::endl; 
}

//  ================================================================================================

int main()
{
	    print(A()     );
	B().print(A()     );
	C().print(A(), B());

	return 0;
}