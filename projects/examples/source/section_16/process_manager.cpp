#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;

#include <boost/process.hpp> 

int main() 
{
	std::cout << "Launching handler ... " << std::endl;

	boost::process::child process("process_handler", boost::process::args({"hello", "world"}));

	std::cout << "Waiting   handler ... " << std::endl;

	std::this_thread::sleep_for(5s); // note: some actions locally

	std::cout << "Verifying handler ... " << std::endl;

	if (process.valid() && process.running())
	{
		std::cout << "Killing   handler ... " << std::endl;

		process.terminate();
	}

	std::cout << process.exit_code() << std::endl; // note: not 0 if terminated

	return 0;
} 