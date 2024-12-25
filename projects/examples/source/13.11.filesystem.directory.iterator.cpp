#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

//  ================================================================================================

auto type(const std::filesystem::file_status & status)
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

//  ================================================================================================

auto permissions(std::filesystem::perms permissions)
{
    auto verify = [permissions](auto bit, auto c) 
    { 
        return (permissions & bit) == std::filesystem::perms::none ? '-' : c; 
    };

    return std::string
    { 
        verify(std::filesystem::perms::owner_read , 'r'),
        verify(std::filesystem::perms::owner_write, 'w'),
        verify(std::filesystem::perms::owner_exec , 'x') 
    };
}

//  ================================================================================================

auto size(const std::filesystem::path & path)
{
	auto result = 0uz;

	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (auto const & entry : std::filesystem::recursive_directory_iterator(path))
		{
			if (!std::filesystem::is_directory(entry.status()))
			{
				result += std::filesystem::file_size(entry);
			}
		}
	}

	return result;
}

//  ================================================================================================

auto size(const std::filesystem::directory_entry & entry)
{
    auto result = 0uz;

    if (std::filesystem::is_regular_file(entry.status()))
    {
        result = std::filesystem::file_size(entry);
    }
    else
    {
        result = size(entry.path());
    }

    std::stringstream sout;

    sout << std::setw(4) << std::setfill(' ') << std::right;

    char letters[]{ 'B', 'K', 'M', 'G' };

    auto index = 0uz;

    for (; index < 3 && result >= 1'024; result /= 1'024, ++index);

    sout << result << letters[index];
    
    return sout.str();
}

//  ================================================================================================

void view(const std::filesystem::path & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
        for (const auto & entry : std::filesystem::directory_iterator(path))
		{
            std::cout << type(entry.status()) << " | ";

            std::cout << permissions(entry.status().permissions()) << " | ";

            std::cout << size(entry) << " | ";

            auto time_point = std::chrono::file_clock::to_sys(entry.last_write_time());

            std::cout << std::chrono::floor < std::chrono::seconds > (time_point) << " | ";

			std::cout << entry.path().filename().string() << '\n';
		}
	}
}

//  ================================================================================================

int main()
{
	view(std::filesystem::current_path());
}