#include <cassert>
#include <filesystem>
#include <iostream>

//  ================================================================================================

[[nodiscard]] std::filesystem::path operator""_p(const char * ptr, std::size_t size)
{
	return std::filesystem::path(std::string(ptr, size));
}

//  ================================================================================================

int main()
{
    std::cout << std::filesystem::current_path() << std::endl;

	const auto path_1 = "../output/./13.09.filesystem.path"_p;

	assert(std::filesystem::exists(path_1));

	std::cout << std::filesystem::absolute (path_1) << std::endl;
    std::cout << std::filesystem::canonical(path_1) << std::endl;

//  ================================================================================================

    try // support: std::filesystem::filesystem_error
	{
        const auto path_2 = "directory/stem.extension"_p;

		std::cout << std::filesystem::canonical(path_2) << std::endl;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n'; 
	}

//  ================================================================================================

	std::cout << ("directory"_p / "stem.extension") << std::endl;

	assert(std::filesystem::equivalent(path_1, "13.09.filesystem.path"));

//  ================================================================================================

    const auto path_3 = std::filesystem::current_path() / "13.09.filesystem.path";

    std::cout << "root_name      = " << path_3.root_name     ().string() << std::endl;
	std::cout << "root_directory = " << path_3.root_directory().string() << std::endl;
	std::cout << "root_path      = " << path_3.root_path     ().string() << std::endl;
	std::cout << "relative_path  = " << path_3.relative_path ().string() << std::endl;
	std::cout << "parent_path    = " << path_3.parent_path   ().string() << std::endl;
	std::cout << "filename       = " << path_3.filename      ().string() << std::endl;
	std::cout << "stem           = " << path_3.stem          ().string() << std::endl;
	std::cout << "extension      = " << path_3.extension     ().string() << std::endl;

	return 0;
}