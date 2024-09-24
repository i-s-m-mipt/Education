#include <cassert>

//  ================================================================================================

class B;

class A
{
public:

	friend inline void test([[maybe_unused]] const A & a);

	friend B;

private:

	const int m_data = 1; 
	
}; // class A

//  ================================================================================================

class C
{
public:

	inline void test([[maybe_unused]] const A & a, 
					 [[maybe_unused]] const B & b) const;

private:

	const int m_data = 1; 
	
}; // class C

//  ================================================================================================

class B
{
public:

	       inline void    test([[maybe_unused]] const A & a) const;
	friend inline void C::test([[maybe_unused]] const A & a, 
							   [[maybe_unused]] const B & b) const;

private:

	const int m_data = 1; 
	
}; // class B

//  ================================================================================================

inline void    test([[maybe_unused]] const A & a)       { assert(a.m_data == 1); }
inline void B::test([[maybe_unused]] const A & a) const { assert(a.m_data == 1); }
inline void C::test([[maybe_unused]] const A & a, 
				    [[maybe_unused]] const B & b) const 
{
//	assert(a.m_data == 1); // error
	assert(b.m_data == 1); 
}

//  ================================================================================================

int main()
{
	    test(A()     );
	B().test(A()     );
	C().test(A(), B());

	return 0;
}