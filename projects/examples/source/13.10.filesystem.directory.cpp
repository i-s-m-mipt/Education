#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

int main()
{
	const auto path = std::filesystem::current_path();

	std::filesystem::create_directory(path / "directory");
	std::filesystem::create_directory(path / "directory", path);

	std::filesystem::create_directories("X/Y/Z");

	std::fstream("X/x.txt", std::ios::out);

	std::filesystem::copy("X/x.txt", "X/y.txt");
	std::filesystem::copy("X/Y",     "X/Z"    );
	std::filesystem::copy("X",       "Y", std::filesystem::copy_options::recursive);

	std::filesystem::rename("Y", "Z");

    std::cout << "Continue? (y/n) "; char c{}; std::cin >> c;

	std::filesystem::remove_all("X");
	std::filesystem::remove_all("Z");

//  std::filesystem::remove_all("C:/"); // note: try it at home yourself

	return EXIT_SUCCESS;
}