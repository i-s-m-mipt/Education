#include <iostream>

class A
{
public:

	friend void print(const A & a);

	friend class B;

private:

	int m_data = 42;

}; // class A

void print(const A & a)
{
	std::cout << a.m_data << std::endl;
}

class B; // note: forward declaration required

class C
{
public:

	void print(const B & b) const;

private:

	int m_data = 42;

}; // class C

class B
{
public:

	void print(const A & a) const
	{
		std::cout << a.m_data << std::endl;
	}

	friend void C::print(const B & b) const; // note: friendship is not transitive

private:

	int m_data = 42;

}; // class B

void C::print(const B & b) const
{
	std::cout << b.m_data << std::endl;
}

int main()
{
	print(A());

	B().print(A());

	C().print(B());

	return 0;
}