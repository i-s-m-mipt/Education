#include <cassert>
#include <iostream>
#include <string>

//  ================================================================================================

class Computer
{
public:

	using integer_t = unsigned int;

	class Tester
	{
	public:

		[[nodiscard]] int test(const Computer & computer) const { return 1; }

	}; // class Tester

//  ================================================================================================

	Computer() : m_name(""), m_data(0)
	{
//		m_name = ""; // error
	}

	Computer(const std::string & name, integer_t data) : m_name(name)
	{
		set_data(data);
	}

	Computer(const std::string & name) : Computer(name, 0) {}

   ~Computer()
	{
		std::cout << "Computer::~Computer" << std::endl;
	}

//  ================================================================================================

	[[nodiscard]] int test_v1() const
	{
//		m_data = m_data_limit; // error

		return 1;
	}

	[[nodiscard]] int test_v2() const;

//  ================================================================================================

	[[nodiscard]] integer_t data() const { return m_data; }

//	void set_data(integer_t data) { m_data = data; } // bad

	void set_data(integer_t data)
	{
		m_data = (data > m_data_limit ? m_data_limit : data); 
		
		m_is_cache_valid = false;
	}

	[[nodiscard]] const std::string & data_as_string() const
	{
		if (!m_is_cache_valid)
		{
			m_data_as_string = std::to_string(m_data);

			m_is_cache_valid = true;
		}

		return m_data_as_string;
	}

//  ================================================================================================

	[[nodiscard]] static integer_t test_v3()
	{
//		m_data = m_data_limit; // error

		return 3;
	}

//  ================================================================================================

	static inline const integer_t m_data_limit = 1;

//  ================================================================================================

private:

	const std::string m_name;

	integer_t m_data = 0;

//  ================================================================================================

	mutable std::string m_data_as_string;

	mutable bool m_is_cache_valid = false;

}; // class Computer

//  ================================================================================================

[[nodiscard]] int Computer::test_v2() const { return 2; }

//  ================================================================================================

int main()
{
	Computer computer_1;

//	computer_1.m_data = 1; // error

	assert(computer_1.test_v1() == 1);
	assert(computer_1.test_v2() == 2);

	computer_1.set_data(1); 
	
	assert(computer_1.data          () ==  1 );
	assert(computer_1.data_as_string() == "1");

//  ================================================================================================

	const Computer computer_2;

	assert(computer_2.test_v1() == 1);
	assert(computer_2.test_v2() == 2);

//  computer_2.set_data(1); // error

	assert(computer_2.data          () ==  0 );
	assert(computer_2.data_as_string() == "0");

//  ================================================================================================

	const Computer computer_3;

	const Computer computer_4("Computer", 1);
	
	const Computer computer_5("Computer");

//	const Computer computer_6(); // error

	{
		const Computer computer_7;
	}

//  ================================================================================================

	assert(Computer::m_data_limit == 1);

	assert(Computer::test_v3() == 3);

	assert(Computer::Tester().test(computer_1) == 1);

	return 0;
}