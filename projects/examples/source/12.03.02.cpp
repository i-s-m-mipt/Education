#include <cctype>
#include <exception>
#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>

///////////////////////////////////////////////////////////////////////////////////////////////////

class Stream
{
public :

	using token_t = std::variant < char, double, std::string > ;

//  -------------------------------------------------------------------------------

	Stream(const std::string & string) : m_stream(string + ';') {}

//  -------------------------------------------------------------------------------

	auto empty()
	{
		return m_stream.peek() == ';';
	}

//  -------------------------------------------------------------------------------

	auto get()
	{
		if (m_has_token) 
		{ 
			m_has_token = false;
			
			return m_token;
		}

		auto x = '\0'; 
		
		m_stream >> x;
		
		switch (x)
		{
			case '+' : case '-' : case '*' : case '/' : case '(' : case ')' : case ';' :
			{
				return token_t(x);
			}
			case '0' : case '1' : case '2' : case '3' : case '4' :

			case '5' : case '6' : case '7' : case '8' : case '9' :

			case '.' :
			{
				m_stream.unget();
				
				auto y = 0.0; 
				
				m_stream >> y;

				return token_t(y);
			}
			default :
			{
				std::string string(1, x);
					
				while (m_stream.get(x) && (std::isalpha(x) || std::isdigit(x)))
				{
					string += x;
				}

				if (!std::isspace(x)) 
				{
					m_stream.unget();
				}

				return token_t(string);
			}
		}
	}

	void putback(const token_t & token)
	{
		m_token = token;
		
		m_has_token = true;
	}

private :

	std::stringstream m_stream;

	token_t m_token;
	
	bool m_has_token = false;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class Calculator
{
public :

	void test()
	{
		std::string string;

		std::cout << "Calculator::test : enter statements : \n";
		
		while (std::getline(std::cin >> std::ws, string))
		{
			if (Stream stream(string); !stream.empty())
			{
				std::cout << "Calculator::test : " << string << " = " << statement(stream) << '\n';
			}
			else 
			{
				break;
			}
		}
	}

private :

	auto statement(Stream & stream) -> double
	{
		auto token = stream.get();

		if (std::holds_alternative < std::string > (token))
		{
			if (std::get < std::string > (token) == "set")
			{
				return declaration(stream);
			}
		}
		
		stream.putback(token);
		
		return expression(stream);
	}

//  -----------------------------------------------------------------------------------------------

	auto declaration(Stream & stream) -> double
	{
		auto string = std::get < std::string > (stream.get());

		m_variables[string] = expression(stream);

		return m_variables[string];
	}

//  -----------------------------------------------------------------------------------------------

	auto expression(Stream & stream) const -> double
	{
		auto x = term(stream);
		
		auto token = stream.get();

		while (true)
		{
			switch (std::get < char > (token))
			{
				case '+' : { x += term(stream); break; }

				case '-' : { x -= term(stream); break; }

				default  : 
				{ 
					stream.putback(token);
						
					return x;
				}
			}

			token = stream.get();
		}
	}

//  -----------------------------------------------------------------------------------------------

	auto term(Stream & stream) const -> double
	{
		auto x = primary(stream);
		
		auto token = stream.get();

		while (true)
		{
			switch (std::get < char > (token))
			{
				case '*' : { x *= term(stream); break; }

				case '/' : { x /= term(stream); break; }

				default  : 
				{ 
					stream.putback(token);
						
					return x;
				}
			}

			token = stream.get();
		}
	}

//  -----------------------------------------------------------------------------------------------

	auto primary(Stream & stream) const -> double
	{
		auto token = stream.get();

		if (std::holds_alternative < char > (token))
		{
			switch (std::get < char > (token))
			{
				case '(' :
				{
					auto x = expression(stream);
					
					stream.get();
					
					return x;
				}
				case '+' : { return      primary(stream); }
				
				case '-' : { return -1 * primary(stream); }
			}
		}
		
		if (std::holds_alternative < double > (token))
		{
			return std::get < double > (token);
		}

		return m_variables.at(std::get < std::string > (token));
	}

//  -----------------------------------------------------------------------------------------------

	std::unordered_map < std::string, double > m_variables;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Calculator().test();
}