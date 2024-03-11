#include <cstdlib>
#include <exception>
#include <stdexcept>

#include "custom_logger.hpp"

using Logger = solution::shared::Logger;

void h()
{
	LOGGER(logger);

	try
	{
		LOGGER_WRITE(logger, "message"); throw std::logic_error("error");
	}
	catch (const std::exception & exception)
	{
		solution::shared::catch_handler < std::runtime_error > (logger, exception);
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