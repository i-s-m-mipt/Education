#include <iostream>

class Exception // note: exceptions hierarchy
{
public:

	Exception(const std::string & message) : m_message(message) {}

	virtual ~Exception() {} 

public:

	virtual std::string what() const
	{
		return m_message;
	}

private:

	std::string m_message;
};

class Error : public Exception
{
public:

	Error(const std::string & message) : Exception(message) {}

public:

	std::string what() const override
	{
		return "error: " + Exception::what();
	}
};

[[noreturn]] void h() // note: control flow will not return to the caller
{
	std::cout << "h() called" << std::endl;

	try
	{
		throw Error("bad function");
	}
	catch (const Error & error)
	{
		std::cout << error.what() << std::endl;

//		throw error; // bad: copy-initialized copy

		throw; // good: rethrow the same exception
	}

//	std::cout << "h() exited" << std::endl; // warning: unreachable code
}

void g()
{
	std::cout << "g() called" << std::endl;

	h();

//	std::cout << "g() exited" << std::endl; // warning: unreachable code
}

void f()
{
	std::cout << "f() called" << std::endl;

	try
	{
		g();
	}
	catch (const Exception & exception)
	{
		std::cout << exception.what() << std::endl;

		throw Exception("new exception"); // note: throw new exception

//		std::cout << "f() exited in catch" << std::endl; // warning: unreachable code
	}

//	std::cout << "f() exited" << std::endl; // warning: unreachable code
}

int main()
{
	try
	{
		f();

		return 0;
	}
	catch (const Exception & exception)
	{
		std::cout << exception.what() << std::endl;

		return -1;
	}
	catch (...) // good: catch all exceptions in main
	{
		std::cout << "unknown exception" << std::endl;

		return -1;
	}
}