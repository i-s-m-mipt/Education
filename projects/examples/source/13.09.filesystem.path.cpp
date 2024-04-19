#include <cassert>
#include <filesystem>
#include <iostream>

[[nodiscard]] std::filesystem::path operator""_p(const char * ptr, std::size_t size)
{
	return std::filesystem::path(std::string(ptr, size));
}

int main()
{
    std::cout << std::filesystem::current_path() << std::endl;

	const auto file = "../output/./13.09.filesystem.path"_p;

	assert(std::filesystem::exists(file));

	std::cout << std::filesystem::absolute (file) << std::endl;
    std::cout << std::filesystem::canonical(file) << std::endl;

    try
	{
        const auto path = "directory/stem.extension"_p;

		std::cout << std::filesystem::canonical(path) << std::endl; // note: weakly canonical
	}
	catch (const std::filesystem::filesystem_error & exception)
	{
		std::cerr << exception.what() << '\n';
	}

	std::cout << ("directory"_p / "stem.extension") << std::endl;

	assert(std::filesystem::equivalent(file, "13.09.filesystem.path"));

    const auto path = std::filesystem::current_path() / "13.09.filesystem.path";

    std::cout << "root_name      = " << path.root_name     ().string() << std::endl;
	std::cout << "root_directory = " << path.root_directory().string() << std::endl;
	std::cout << "root_path      = " << path.root_path     ().string() << std::endl;
	std::cout << "relative_path  = " << path.relative_path ().string() << std::endl;
	std::cout << "parent_path    = " << path.parent_path   ().string() << std::endl;
	std::cout << "filename       = " << path.filename      ().string() << std::endl;
	std::cout << "stem           = " << path.stem          ().string() << std::endl;
	std::cout << "extension      = " << path.extension     ().string() << std::endl;

	return 0;
}