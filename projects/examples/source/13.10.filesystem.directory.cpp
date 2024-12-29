#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>

int main()
{
	auto path = std::filesystem::current_path();

	std::filesystem::create_directory(path / "directory");

	std::filesystem::create_directory(path / "directory", path);

	std::filesystem::create_directories("X/Y/Z");

//  ================================================================================================

	if (std::fstream fout("X/x.txt", std::ios::out); !fout)
	{
		throw std::runtime_error("invalid stream");
	}

	std::filesystem::copy("X/x.txt", "X/y.txt");

	std::filesystem::copy("X/Y", "X/Z");
	
	std::filesystem::copy("X", "Y", std::filesystem::copy_options::recursive);

	std::filesystem::rename("Y", "Z");

//  ================================================================================================

    std::cout << "main : enter char to continue : "; char c; std::cin >> c;

	std::filesystem::remove_all("X");
	
	std::filesystem::remove_all("Z");

	std::filesystem::remove_all(path / "directory");

//  std::filesystem::remove_all("C:/"); // bad
}