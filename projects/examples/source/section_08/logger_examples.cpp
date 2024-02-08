#include <cstdlib>
#include <exception>
#include <stdexcept>

#include "custom_logger.hpp"

using Logger = solution::shared::Logger;

class demo_exception : public std::runtime_error
{
public:

	explicit demo_exception(const std::string & message) noexcept : std::runtime_error(message.c_str()) {}

}; // class demo_exception : public std::runtime_error

void h()
{
	LOGGER(logger);

	try
	{
		LOGGER_WRITE(logger, "message"); throw std::runtime_error("error");
	}
	catch (const std::exception & exception)
	{
		solution::shared::catch_handler < demo_exception > (logger, exception);
	}
}

void g() { LOGGER(logger); h(); }
void f() { LOGGER(logger); g(); }

int main()
{
	LOGGER(logger);

	try
	{
		f();

		return EXIT_SUCCESS;
	}
	catch (const std::exception & exception)
	{
		LOGGER_WRITE_FATAL(logger, exception.what());

		return EXIT_FAILURE;
	}
	catch (...)
	{
		LOGGER_WRITE_FATAL(logger, "unknown exception");

		return EXIT_FAILURE;
	}
}