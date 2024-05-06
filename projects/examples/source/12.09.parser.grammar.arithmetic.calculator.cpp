#include <cctype>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>

using namespace std::literals;

//  ================================================================================================

class Stream
{
public:

	using Token = std::variant < char, double, std::string > ;

public:

	explicit Stream(const std::string & data) noexcept : m_is_full(false), m_sin(data + ';') {}

public:

	[[nodiscard]] bool empty() noexcept
	{
		char c{}; 

		if (m_sin >> c; c != ';') { m_sin.putback(c); return false; } else return true;
	}

	[[nodiscard]] Token get()
	{
		if (m_is_full) { m_is_full = false; return m_token; }

		char c{}; 
		
		switch (m_sin >> c; c)
		{
			case '+': case '-': case '*': case '/': 
			case '(': case ')': case ';':
			{
				return Token(c);
			}
			case '.':
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			{
				m_sin.putback(c); double value{}; m_sin >> value;

				return Token(value);
			}
			[[unlikely]] default:
			{
				if (std::string string(1, c); std::isalpha(c))
				{
					while (m_sin.get(c) && (std::isalpha(c) || std::isdigit(c))) string += c;

					if (!std::isspace(c)) m_sin.putback(c); 

					return Token(string);
				}
				else throw std::runtime_error("invalid token: "s + c);
			}
		}
	}

	void putback(const Token & token) noexcept
	{
		m_token = token; m_is_full = true;
	}

private:

	Token m_token; bool m_is_full; std::stringstream m_sin;

}; // class Stream

//  ================================================================================================

class Calculator
{
public:

	void run()
	{
		for (std::string line; std::getline(std::cin >> std::ws, line); )
		{
			if (Stream stream(line); !stream.empty())
			{
				std::cout << "= " << statement(stream) << std::endl;
			}
			else break;			
		}
	}

private:

	[[nodiscard]] double statement(Stream & stream)
	{
		const auto token = stream.get();

		if (std::holds_alternative < std::string > (token) && 
			std::get               < std::string > (token) == "set")
		{
			return declaration(stream);
		}
		
		stream.putback(token); return expression(stream);
	}

	[[nodiscard]] double declaration(Stream & stream)
	{
		const auto name = std::get < std::string > (stream.get());

		m_variables[name] = expression(stream);

		return m_variables[name];
	}

	[[nodiscard]] double expression(Stream & stream) const
	{
		auto left = term(stream);

		for (auto token = stream.get(); true; token = stream.get())
		{
			if (std::holds_alternative < char > (token))
			{
				switch (std::get < char > (token))
				{
					case '+': { left += term(stream); break; }
					case '-': { left -= term(stream); break; }

					default: { stream.putback(token); return left; }
				}
			}
			else throw std::runtime_error("invalid expression");
		}
	}

	[[nodiscard]] double term(Stream & stream) const
	{
		auto left = primary(stream);

		for (auto token = stream.get(); true; token = stream.get())
		{
			if (std::holds_alternative < char > (token))
			{
				switch (std::get < char > (token))
				{
					case '*': { left *= term(stream); break; }
					case '/': { left /= term(stream); break; }

					default: { stream.putback(token); return left; }
				}
			}
			else throw std::runtime_error("invalid term");
		}
	}

	[[nodiscard]] double primary(Stream & stream) const
	{
		auto token = stream.get();

		if (std::holds_alternative < char > (token))
		{
			switch (std::get < char > (token))
			{
				case '(':
				{
					const auto d = expression(stream); 
					
					token = stream.get(); 

					if (!std::holds_alternative < char > (token) || 
						 std::get               < char > (token) != ')')
					{
						throw std::runtime_error("invalid token, ) expected");
					}
					
					return d;
				}

				case '+': return        primary(stream);
				case '-': return -1.0 * primary(stream);
				
				default: throw std::runtime_error("invalid primary");
			}
		}
		
		if (std::holds_alternative < double > (token))
		{
			return std::get < double > (token);
		}

		return m_variables.at(std::get < std::string > (token));
	}

private:

	mutable std::unordered_map < std::string, double > m_variables;

}; // class Calculator

//  ================================================================================================

int main()
{
	try
	{
		Calculator().run();

		return EXIT_SUCCESS;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n';

		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "unknown exception\n";

		return EXIT_FAILURE;
	}
}