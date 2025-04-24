//////////////////////////////////////////////////////////////////////////////////////

// support : ls -la

//////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <chrono>
#include <filesystem>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

//////////////////////////////////////////////////////////////////////////////////////

auto type(std::filesystem::file_status const & status)
{
    if (std::filesystem::is_block_file    (status)) { return 'b'; }
    
    if (std::filesystem::is_character_file(status)) { return 'c'; }

    if (std::filesystem::is_directory     (status)) { return 'd'; }

    if (std::filesystem::is_fifo          (status)) { return 'p'; }

    if (std::filesystem::is_other         (status)) { return 'o'; }

    if (std::filesystem::is_regular_file  (status)) { return 'f'; }

    if (std::filesystem::is_socket        (status)) { return 's'; }

    if (std::filesystem::is_symlink       (status)) { return 'l'; }

    return '?';
}

//////////////////////////////////////////////////////////////////////////////////////

auto permissions(std::filesystem::perms permissions) -> std::string
{
    auto lambda = [permissions](auto x, auto y) 
    { 
        return (permissions & x) == std::filesystem::perms::none ? '-' : y;
    };

    return
    { 
        lambda(std::filesystem::perms::owner_read,  'r'),

        lambda(std::filesystem::perms::owner_write, 'w'),

        lambda(std::filesystem::perms::owner_exec,  'x') 
    };
}

//////////////////////////////////////////////////////////////////////////////////////

auto size(std::filesystem::path const & path)
{
	auto size = 0uz;

	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (auto const & entry : std::filesystem::recursive_directory_iterator(path))
		{
			if (!std::filesystem::is_directory(entry.status()))
			{
				size += std::filesystem::file_size(entry);
			}
		}
	}

	return size;
}

//////////////////////////////////////////////////////////////////////////////////////

auto size(std::filesystem::directory_entry const & entry)
{
    auto size = 0uz;

    if (std::filesystem::is_regular_file(entry.status()))
    {
        size = std::filesystem::file_size(entry);
    }
    else
    {
        size = ::size(entry.path());
    }

    std::array < char, 4 > array = { 'B', 'K', 'M', 'G' };

    auto i = 0uz;

    while (i++ < 3 && size >= 1'024)
    {
        size /= 1'024;
    }

    return (std::stringstream() << std::format("{: >4}", size) << array[i - 1]).str();
}

//////////////////////////////////////////////////////////////////////////////////////

void test(std::filesystem::path const & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
        for (auto const & entry : std::filesystem::directory_iterator(path))
		{
            std::cout << "test : entry : " << type(entry.status());

            std::cout << " | " << permissions(entry.status().permissions());

            std::cout << " | " << size(entry);

            std::cout << " | " << std::chrono::floor < std::chrono::seconds > 
            (
                std::chrono::file_clock::to_sys(entry.last_write_time())
            );

			std::cout << " | " << entry.path().filename().string() << '\n';
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
	test(std::filesystem::current_path());
}

//////////////////////////////////////////////////////////////////////////////////////