#include <cassert>
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////

auto operator""_p(const char * string, std::size_t size)
{
	return std::filesystem::path(std::string(string, size));
}

////////////////////////////////////////////////////////////////

int main()
{
	auto path_1 = "../output/./13.09.filesystem.path"_p;

	auto path_2 = std::filesystem::absolute (path_1);

	auto path_3 = std::filesystem::canonical(path_1);

	auto path_4 = std::filesystem::current_path();

	auto path_5 = std::filesystem::current_path().parent_path();

//  ------------------------------------------------------------

	assert(std::filesystem::exists(path_1));

	assert(path_1.filename() == "13.09.filesystem.path");

	assert(path_2 != path_3);
	
	assert(std::filesystem::equivalent(path_2, path_3));

//  ------------------------------------------------------------

	std::cout << "path_2 = " << path_2 << '\n';

	std::cout << "path_3 = " << path_3 << '\n';

	std::cout << "path_4 = " << path_4 << '\n';

	std::cout << "path_5 = " << path_5 << '\n';

//  ------------------------------------------------------------

    try
	{
        auto path_6 = "directory"_p / "stem.extension"_p;

		auto path_7 = std::filesystem::canonical(path_6);
	}
	catch (const std::filesystem::filesystem_error & exception)
	{
		std::cerr << "main : " << exception.what() << '\n'; 
	}
}