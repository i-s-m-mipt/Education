#include <iostream>

class Date
{
public: // good: public members last

	using integer_t = int;

public:

	Date() : m_year(0), m_month(0), m_day(0) // good: initializer list, initialization
	{
//		m_year  = 0; // bad: assignment, not initialization
//		m_month = 0;
//		m_day   = 0;

		initialize(); // good: don't repeat yourself
	}

	Date(integer_t year, integer_t month, integer_t day) : // note: default arguments?
		m_year(year), m_month(month), m_day(day) // note: member initialization order
	{
		initialize();
	}

	Date(integer_t year) : Date(year, 1, 1) // good: delegating constructor
	{
		initialize();
	}

public:

	void initialize()
	{
		// ...
	}

public:

	void print_v1() const // note: defined in class is inline by default
	{
		std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
	}

	void print_v2() const;

public:

	[[nodiscard]] auto year() const // good: auto in a one-liner function
	{
		return m_year;
	}

/*
	void set_year(int year) // bad: trivial getter and setter pair
	{
		m_year = year;
	}
*/

	void set_year(integer_t year) // good: setter with additional actions
	{
		m_year = (year < 0 ? 0 : year > 9999 ? 9999 : year);
	}

	void set_year_from_date(const Date & date)
	{
		set_year(date.m_year); // note: partial assignment
	}

private: // good: private members last

	integer_t m_year  = 0; // good: name begins with m_
	integer_t m_month = 0;
	integer_t m_day   = 0;
};

void Date::print_v2() const
{
	const auto separator = '/';

	if (m_year < 1000) std::cout << '0';
	if (m_year <  100) std::cout << '0';
	if (m_year <   10) std::cout << '0';
	 
	std::cout << m_year << separator;

	if (m_month < 10) std::cout << '0';

	std::cout << m_month << separator;

	if (m_day < 10) std::cout << '0';

	std::cout << m_day << '\n';
}

int main()
{
	Date date; // note: default constructor

//	date.m_year = 2023; // error: private data

	date.print_v1();
	date.print_v2();

	[[maybe_unused]] auto year = date.year();

	date.set_year(2023);

	Date date_1;
	Date date_2(2023, 19, 9);

//	Date date_3(); // bad: most vexing parse, not an instance of class

	return 0;
}