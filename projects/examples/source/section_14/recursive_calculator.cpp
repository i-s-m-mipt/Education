#include <cctype>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <string>
#include <variant>

class Stream
{
public:

	using Token = std::variant < std::monostate, char, double, std::string > ;

public:

	explicit Stream(const std::string & data) noexcept : m_is_full(false), m_sin(data + semicolon) {}

public:

	[[nodiscard]] bool empty() noexcept
	{
		char c{}; m_sin >> c;

		if (c != semicolon)
		{
			m_sin.putback(c); return false;
		}
		else return true;
	}

	[[nodiscard]] Token get()
	{
		if (m_is_full) { m_is_full = false; return m_token; }

		char c{}; m_sin >> c;
		
		switch (c)
		{
			case '=': case '!': case '(': case ')':
			case '+': case '-': case '*': case '/': case semicolon:
				return Token(c);
			case '.':
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			{
				m_sin.putback(c);

				double value{}; m_sin >> value;

				return Token(value);
			}
			[[unlikely]] default:
			{
				if (std::string string(1, c); std::isalpha(c))
				{
					while (m_sin.get(c) && (std::isalpha(c) || std::isdigit(c))) string += c;

					if (std::isspace(c)) 
					{
						m_sin.putback(c); return Token(string);
					}
					else throw std::runtime_error("invalid input");
				}
				else throw std::runtime_error("invalid input");
			}
		}
	}

	void putback(const Token & token) noexcept
	{
		m_token = token; m_is_full = true;
	}

private:

	static inline const auto semicolon = ';';

private:

	Token m_token; bool m_is_full; std::stringstream m_sin;

}; // class Stream

struct Variable { std::string name; double value{}; };




	Token::value_t expression(Stream& Stream, const std::vector < Variable >& variables);
	Token::value_t term(Stream& Stream, const std::vector < Variable >& variables);
	Token::value_t statement(Stream& Stream, std::vector < Variable >& variables);
	Token::value_t primary(Stream& Stream, const std::vector < Variable >& variables);

	Token::value_t get_value(const std::string& n, const std::vector < Variable >& variables);
	bool is_declared(const std::string& n, const std::vector < Variable >& variables) noexcept;
	Token::value_t set_variable(const std::string& n, Token::value_t v, std::vector < Variable >& variables);
	Token::value_t declaration(Stream& Stream, std::vector < Variable >& variables);

	Token::value_t primary(Stream& Stream, const std::vector < Variable >& variables)
	{
		auto t = Stream.get();

		switch (t.kind)
		{
		case Token::variable:
			return get_value(t.name, variables);
		case '(':
		{
			auto d = expression(Stream, variables);
			t = Stream.get();
			return d;
		}
		case Token::number:
			return t.value;
		case '-':
			return Token::value_t(-1) * primary(Stream, variables);
		case '+':
			return primary(Stream, variables);
		default:
		{
			throw std::ios_base::failure("error: cannot read the symbol");
		}
		}
	}

	Token::value_t expression(Stream& Stream, const std::vector < Variable >& variables)
	{
		auto left = term(Stream, variables);

		auto t = Stream.get();

		while (true)
		{
			switch (t.kind)
			{
			case '+':
				left = left + term(Stream, variables);
				t = Stream.get();
				break;
			case '-':
				left = left - term(Stream, variables);
				t = Stream.get();
				break;
			default:
				Stream.putback(t);
				return left;
			}
		}
	}

	Token::value_t statement(Stream& Stream, std::vector < Variable >& variables)
	{
		auto token = Stream.get();

		switch (token.kind)
		{
		case Token::set:
			return declaration(Stream, variables);
		default:
			Stream.putback(token);
			return expression(Stream, variables);
		}
	}

	Token::value_t term(Stream& Stream, const std::vector < Variable >& variables)
	{
		auto left = primary(Stream, variables);

		auto t = Stream.get();

		while (true)
		{
			switch (t.kind)
			{
			case '!':
			{
				left = fact(left);
				t = Stream.get();
				break;
			}
			case '*':
				left = left * primary(Stream, variables);
				t = Stream.get();
				break;
			case '/':
			{
				left = left / primary(Stream, variables);
				t = Stream.get();
				break;
			}
			default:
				Stream.putback(t);
				return left;
			}
		}
	}

	Token::value_t get_value(const std::string& n, const std::vector < Variable >& variables)
	{
		if (!is_declared(n, variables))
		{
			throw std::ios_base::failure("error: incorrect input data");
		}

		for (const Variable& variable : variables)
		{
			if (variable.name == n)
			{
				return variable.value;
			}
		}
	}

	Token::value_t declaration(Stream& Stream, std::vector < Variable >& variables)
	{
		Token token = Stream.get();
		std::string name = token.name;
		Token assume = Stream.get();
		auto value = expression(Stream, variables);

		set_variable(name, value, variables);

		return value;
	}

	bool is_declared(const std::string& n, const std::vector < Variable >& variables) noexcept
	{
		for (const Variable& variable : variables)
		{
			if (variable.name == n)
			{
				return true;
			}
		}
		return false;
	}

	Token::value_t set_variable(const std::string& n, Token::value_t v, std::vector < Variable >& variables)
	{
		if (is_declared(n, variables))
		{
			throw std::ios_base::failure("error: incorrect input data");
		}

		for (auto& variable : variables)
		{
			if (variable.name == n)
			{
				variable.value = v;
				return v;
			}
		}

		variables.push_back(Variable(n, v));

		return v;
	}

	struct IO_Service
	{
		struct Command
		{
			static inline const auto exit = "exit";
			static inline const auto help = "help";
		};

		auto read() noexcept
		{
			std::cout << ">>> ";

			std::string line;
			std::string head;
			std::string tail;

			std::cin >> head;

			if (head == Command::exit)
			{
				exit(0);
			}
			else
				if (head == Command::help)
				{
					std::cout << "Welcome to Calculator!" << std::endl;
				}
				else
				{
					line += head;
				}

			std::getline(std::cin, tail);

			line += tail;

			return line;
		}

		void write(const std::string& s) noexcept
		{
			std::cout << "= " << s << std::endl;
		}
	};

	struct Calculator
	{
		auto run(Stream& ts)
		{
			return statement(ts, variables);
		}

		std::vector < Variable > variables;
	};

	struct System
	{
		void run()
		{
			while (true)
			{
				Stream ts(io_service.read());

				if (ts.empty())
				{
					continue;
				}

				std::stringstream sout;

				sout << calculator.run(ts);

				io_service.write(sout.str());
			}
		}

		IO_Service io_service;
		Calculator calculator;
	};

int main() try
{
	calculator::System s;

	s.run();

	return 0;
}
catch (const std::ios_base::failure& exception)
{
	std::cerr << exception.what() << std::endl;
	return 0;
}
catch (const std::exception& exception)
{
	std::cerr << exception.what() << std::endl;
	return 0;
}
catch (...)
{
	std::cerr << "there is an exception" << std::endl;
	return 0;
}