#include <detail.hpp>
#include <logger.hpp>

#include "system/system.hpp"

using Logger = enclave::shared::Logger;
using System = enclave::system::System;

int main(int argc, char ** argv)
{
	LOGGER(logger);

	try
	{
		System(argc, argv).run();

		return EXIT_SUCCESS;
	}
	catch (const std::exception & exception)
	{
		LOGGER_WRITE_FATAL(logger, exception.what());
	}
	catch (...)
	{
		LOGGER_WRITE_FATAL(logger, "unknown exception");
	}

	return EXIT_FAILURE;
}