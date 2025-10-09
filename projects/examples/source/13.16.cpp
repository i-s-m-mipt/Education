////////////////////////////////////////////////////////////////////////////////

#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto path = std::filesystem::current_path();

//  ----------------------------------------------------------------------------

	std::filesystem::create_directory(path / "directory");

	std::filesystem::create_directory(path / "directory", path);

//  ----------------------------------------------------------------------------

	std::filesystem::create_directories("a1/b/c");

//  ----------------------------------------------------------------------------

	std::fstream("a1/b/c/output.data", std::ios::out);

//  ----------------------------------------------------------------------------

	std::filesystem::copy("a1", "a2");
		
	std::filesystem::copy("a1", "a2", std::filesystem::copy_options::recursive);

//  ----------------------------------------------------------------------------

	std::cout << "main : enter char : "; std::cin.get();

//  ----------------------------------------------------------------------------

	std::filesystem::remove_all("a1");
	
	std::filesystem::remove_all("a2");

//  ----------------------------------------------------------------------------

	std::filesystem::remove_all(std::filesystem::current_path() / "directory");

//  ----------------------------------------------------------------------------

//  std::filesystem::remove_all("/"); // bad
}

////////////////////////////////////////////////////////////////////////////////