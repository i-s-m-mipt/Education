#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;

#include <boost/process.hpp> 

int main() 
{
	std::cout << "Launching handler ... " << '\n';

	boost::process::child process("process_handler", boost::process::args({"hello", "world"}));

	std::cout << "Waiting   handler ... " << '\n';

	std::this_thread::sleep_for(5s);

	std::cout << "Verifying handler ... " << '\n';

	if (process.valid() && process.running())
	{
		std::cout << "Killing   handler ... " << '\n';

		process.terminate();
	}

	std::cout << process.exit_code() << '\n';
} 