#include <iostream>
#include <string>

//  ================================================================================================

class Date
{
public:

	using integer_t = unsigned int;

	class Printer
	{
	public:

		void print(const Date & date) const
		{
			std::cout << date.m_year << '/' << date.m_month << '/' << date.m_day << std::endl;
		}

	}; // class Printer

public:

	Date() : m_year(0), m_month(0), m_day(0) 
	{
//		m_year = 0; m_month = 0; m_day = 0; // bad	

		initialize(); 
	}

	Date(integer_t year, integer_t month, integer_t day) : m_year(year), m_month(month), m_day(day)
	{
		initialize();
	}

	Date(integer_t year) : Date(year, 1, 1)
	{
		initialize();
	}

   ~Date()
	{
		uninitialize();
	}

private:

	void   initialize() { ++m_counter; }
	void uninitialize() { --m_counter; }

public:

	void print_v1() const
	{
//		m_year = 2023; // error

		std::cout << prompt << m_year << '/' << m_month << '/' << m_day << std::endl;
	}

	void print_v2() const;

public:

	[[nodiscard]] integer_t year() const { return m_year; }

//	void set_year(integer_t year) { m_year = year; } // bad

	void set_year(integer_t year)
	{
		m_year = (year > max_year ? max_year : year); 
		
		m_is_string_valid = false;
	}

	[[nodiscard]] const std::string & get_date_as_string() const
	{
		if (!m_is_string_valid)
		{
			m_date_as_string = std::to_string(m_year ) + '/' +
							   std::to_string(m_month) + '/' +
							   std::to_string(m_day  );

			m_is_string_valid = true;
		}

		return m_date_as_string;
	}

public:

	[[nodiscard]] static std::size_t counter() { return m_counter; }

public:

	static inline const integer_t max_year = 9999;

	static inline const std::string prompt = "date: ";

private:

	static inline std::size_t m_counter = 0;

private:

	integer_t m_year  = 0;
	integer_t m_month = 0;
	integer_t m_day   = 0;

private:

	mutable std::string m_date_as_string;

	mutable bool m_is_string_valid = false;

}; // class Date

//  ================================================================================================

void Date::print_v2() const
{
	std::cout << prompt;

	if (m_year < 1000) std::cout << '0';
	if (m_year <  100) std::cout << '0';
	if (m_year <   10) std::cout << '0';

	const auto separator = '/';
	 
	std::cout << m_year  << separator; if (m_month < 10) std::cout << '0';
	std::cout << m_month << separator; if (m_day   < 10) std::cout << '0';
	std::cout << m_day   << std::endl;
}

//  ================================================================================================

int main()
{
	Date date;

//	date.m_year = 2023; // error

	date.print_v1();
	date.print_v2();

	[[maybe_unused]] const auto year = date.year();

	date.set_year(2023);

//  ================================================================================================

	const Date c_date;

	c_date.print_v2();

//	c_date.set_year(2023); // error

	std::cout << c_date.get_date_as_string() << std::endl;

//  ================================================================================================

	const Date date_1;
	
	const Date date_2(2023, 9, 19);

//	const Date date_3(); // error

//	const Date date_4{}; // bad

//  ================================================================================================

	Date::Printer().print(date_2);

//  ================================================================================================

	std::cout << date_1.max_year << std::endl;
	std::cout << date_2.max_year << std::endl;
	std::cout << Date:: max_year << std::endl;
	std::cout << Date::counter() << std::endl;

	return 0;
}