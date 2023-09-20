#include <iostream>

class A
{
public:

	A()
	{
//		print(); // bad: base version
	}

	virtual ~A()
	{
//		print(); // bad: base version
	}

public:

	virtual void print() const
	{
		std::cout << "A\n";
	}
};

class B final : public A
{
public:

	B(int number) : m_number(number) {}

public:

	void print() const override final
	{
		std::cout << "B " << m_number << '\n';
	}

private:

	int m_number = 0;
};

/*
class C final : public B // error: declared final
{
public:

	void print() const override // error: declared final
	{
		std::cout << "C\n";
	}
};
*/

int main()
{
	B b(0);

	A * a_ptr = &b; // note: works with pointers and references

	a_ptr->print();

	const auto size = 3;

	B b1(1);
	B b2(2);
	B b3(3);

	A * pointers[size]{ &b1, &b2, &b3 };

	for (auto i = 0; i < size; ++i)
	{
		pointers[i]->print();
	}

	a_ptr = new B(0);

	a_ptr->print();

	delete a_ptr; // note: important virtual destructor

	return 0;
}