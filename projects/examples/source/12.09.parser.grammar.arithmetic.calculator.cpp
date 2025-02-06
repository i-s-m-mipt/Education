#include <cctype>
#include <exception>
#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>

//  ================================================================================================

using Token = std::variant < char, double, std::string > ;

//  ================================================================================================

class Stream
{
public:

	Stream(const std::string & string) : m_stream(string + ';') {}

//  ----------------------------------------------------------------

	auto empty()
	{
		auto x = '\0'; m_stream >> x;

		if (x != ';') 
		{ 
			m_stream.putback(x); return false; 
		} 
		else 
		{
			return true;
		}
	}

	auto get()
	{
		if (m_has_token) 
		{ 
			m_has_token = false; return m_token; 
		}

		auto x = '\0'; m_stream >> x;
		
		switch (x)
		{
			case '+': case '-': case '*': case '/': 
			case '(': case ')': case ';':
			{
				return Token(x);
			}
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case '.':
			{
				m_stream.putback(x); auto y = 0.0; m_stream >> y;

				return Token(y);
			}
			default:
			{
				if (std::isalpha(x))
				{
					std::string string(1, x);
					
					while (m_stream.get(x) && (std::isalpha(x) || std::isdigit(x))) 
					{
						string += x;
					}

					if (!std::isspace(x)) 
					{
						m_stream.putback(x); 
					}

					return Token(string);
				}
				else 
				{
					throw std::runtime_error("invalid token");
				}
			}
		}
	}

	void putback(const Token & token)
	{
		m_token = token; m_has_token = true;
	}

private:

	std::stringstream m_stream; bool m_has_token = false; Token m_token;
};

//  ================================================================================================

class Calculator
{
public:

	void test()
	{
		std::cout << "Calculator::test : enter statements : \n"; std::string string;

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

private:

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

	auto declaration(Stream & stream) -> double
	{
		auto string = std::get < std::string > (stream.get());

		m_variables[string] = expression(stream);

		return m_variables[string];
	}

	auto expression(Stream & stream) const -> double
	{
		auto x = term(stream); auto token = stream.get();

		while (true)
		{
			if (std::holds_alternative < char > (token))
			{
				switch (std::get < char > (token))
				{
					case '+': { x += term(stream); break; }

					case '-': { x -= term(stream); break; }

					default: 
					{ 
						stream.putback(token); 
						
						return x; 
					}
				}
			}
			else 
			{
				throw std::runtime_error("invalid expression");
			}

			token = stream.get();
		}
	}

	auto term(Stream & stream) const -> double
	{
		auto x = primary(stream); auto token = stream.get();

		while (true)
		{
			if (std::holds_alternative < char > (token))
			{
				switch (std::get < char > (token))
				{
					case '*': { x *= term(stream); break; }

					case '/': { x /= term(stream); break; }

					default: 
					{ 
						stream.putback(token); 
						
						return x; 
					}
				}
			}
			else 
			{
				throw std::runtime_error("invalid term");
			}

			token = stream.get();
		}
	}

	auto primary(Stream & stream) const -> double
	{
		auto token = stream.get();

		if (std::holds_alternative < char > (token))
		{
			switch (std::get < char > (token))
			{
				case '(':
				{
					auto x = expression(stream); 
					
					token = stream.get(); 

					if (!std::holds_alternative < char > (token))
					{
						throw std::runtime_error("invalid token");
					}

					if (std::get < char > (token) != ')')
					{
						throw std::runtime_error("invalid token");
					}
					
					return x;
				}
				case '+': { return        primary(stream); }
				
				case '-': { return -1.0 * primary(stream); }
				
				default: 
				{
					throw std::runtime_error("invalid primary");
				}
			}
		}
		
		if (std::holds_alternative < double > (token))
		{
			return std::get < double > (token);
		}

		return m_variables.at(std::get < std::string > (token));
	}

//  -------------------------------------------------------

	std::unordered_map < std::string, double > m_variables;
};

//  ================================================================================================

int main()
{
	Calculator().test();
}