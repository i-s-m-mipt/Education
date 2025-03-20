#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////

int main()
{
	auto path = std::filesystem::current_path();

//  ---------------------------------------------------------------------------

	std::filesystem::create_directory(path / "directory");

	std::filesystem::create_directory(path / "directory", path);

	std::filesystem::create_directories("a/b/c");

//  ---------------------------------------------------------------------------

	std::cout << "main : enter char : "; std::cin.get();

//  ---------------------------------------------------------------------------

	std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');

//  ---------------------------------------------------------------------------

	if (std::fstream stream("a/file.data"); !stream)
	{
		throw std::runtime_error("invalid stream");
	}

//  ---------------------------------------------------------------------------

	std::filesystem::copy("a/file.data", "a/b/file.data");

	std::filesystem::copy("a/b", "a/d");
		
	std::filesystem::copy("a", "e", std::filesystem::copy_options::recursive);

//  ---------------------------------------------------------------------------

	std::filesystem::rename("e", "f");

//  ---------------------------------------------------------------------------

	std::cout << "main : enter char : "; std::cin.get();

//  ---------------------------------------------------------------------------

	std::filesystem::remove_all("a");
	
	std::filesystem::remove_all("f");

	std::filesystem::remove_all(std::filesystem::current_path() / "directory");

//  std::filesystem::remove_all("/"); // bad
}