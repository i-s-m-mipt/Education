#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "logger/logger.hpp"
#include "system/system.hpp"

using Logger = solution::shared::Logger;
using System = solution::system::System;

int main(int argc, char** argv)
{
	LOGGER(logger);

	try
	{
		{
			System system;

			system.run();
		}

		system("pause");

		return EXIT_SUCCESS;
	}
	catch (const std::exception& exception)
	{
		LOGGER_WRITE_FATAL(logger, exception.what());

		system("pause");

		return EXIT_FAILURE;
	}
	catch (...)
	{
		LOGGER_WRITE_FATAL(logger, "unknown exception");

		system("pause");

		return EXIT_FAILURE;
	}
}