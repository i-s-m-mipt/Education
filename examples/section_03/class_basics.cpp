#include <iostream>

class Date // note: pay attention to the order of class members
{
public: // good: public members first

	using integer_t = int;

public:

	class Printer // note: nested types can’t be forward declared
	{
	public:

		void print(const Date & date) const
		{
			std::cout << date.m_year << '/' << date.m_month << '/' << date.m_day << std::endl;
		}

	}; // class Printer

public:

	Date() : m_year(0), m_month(0), m_day(0) // good: initializer list, initialization
	{
//		m_year  = 0; // bad: assignment, not initialization
//		m_month = 0;
//		m_day   = 0;

		initialize(); // good: don't repeat yourself
	}

	Date(integer_t year, integer_t month, integer_t day) : 
		m_year(year), m_month(month), m_day(day) // note: member initialization order
	{
		initialize();
	}

	Date(integer_t year) : Date(year, 1, 1) // good: delegating constructor
	{
		initialize();
	}

	~Date() // note: don't call destructor explicitly
	{
		uninitialize();
	}

public:

	void initialize()
	{
		++counter;
	}

	void uninitialize()
	{
		--counter;
	}

public:

	void print_v1() const // note: small function is defined in the class as inline
	{
//		m_year = 2023; // error: const function

		std::cout << m_year << '/' << m_month << '/' << m_day << std::endl;
	}

	void print_v2() const;

public:

	[[nodiscard]] auto year() const // good: auto in a one-liner function
	{
		return m_year;
	}

/*
	void set_year(integer_t year) // bad: trivial getter and setter pair
	{
		m_year = year;
	}
*/

	void set_year(integer_t year) // good: setter with additional actions
	{
		m_year = (year < 0 ? 0 : year > max_year ? max_year : year);
	}

	void set_year_from_date(const Date & date)
	{
		set_year(date.m_year); // note: partial assignment
	}

public:

	static auto get_counter()
	{
		return counter;
	}

public:

	static inline const int max_year = 9999; // note: common for all instances

private:

	static inline int counter = 0;

private: // good: private members last

	integer_t m_year  = 0; // good: name begins with m_ prefix
	integer_t m_month = 0;
	integer_t m_day   = 0;

}; // class Date

void Date::print_v2() const // good: large function is defined outside the class
{
	const auto separator = '/';

	if (m_year < 1000) std::cout << '0';
	if (m_year <  100) std::cout << '0';
	if (m_year <   10) std::cout << '0';
	 
	std::cout << m_year  << separator; if (m_month < 10) std::cout << '0';
	std::cout << m_month << separator; if (m_day   < 10) std::cout << '0';
	std::cout << m_day   << std::endl;
}

int main()
{
	Date date; // note: default constructor

//	date.m_year = 2023; // error: private data

	date.print_v1();
	date.print_v2();

	[[maybe_unused]] auto year = date.year();

	date.set_year(2023);

	[[maybe_unused]] const Date c_date;

	c_date.print_v2();

//	c_date.set_year(2023); // error: non-constant member function

	Date date_1;
	Date date_2(2023, 9, 19);

//	Date date_3(); // bad: most vexing parse, not an instance of the class

	Date::Printer printer;

	printer.print(date_2);

	std::cout << date_1.max_year << std::endl;
	std::cout << date_2.max_year << std::endl;

	std::cout << Date::max_year << std::endl; // good: preferred syntax

	std::cout << Date::get_counter() << std::endl;

	return 0;
}