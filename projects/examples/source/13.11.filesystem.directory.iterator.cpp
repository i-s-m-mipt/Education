#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

// =================================================================================================

[[nodiscard]] char entry_type(const std::filesystem::file_status & status) noexcept
{
         if (std::filesystem::is_block_file    (status)) { return 'b'; }
    else if (std::filesystem::is_character_file(status)) { return 'c'; }
    else if (std::filesystem::is_directory     (status)) { return 'd'; }
    else if (std::filesystem::is_fifo          (status)) { return 'p'; }
    else if (std::filesystem::is_other         (status)) { return 'o'; }
    else if (std::filesystem::is_regular_file  (status)) { return 'f'; }
    else if (std::filesystem::is_socket        (status)) { return 's'; }
    else if (std::filesystem::is_symlink       (status)) { return 'l'; }

    return '?';
}

// =================================================================================================

[[nodiscard]] std::string entry_permissions(std::filesystem::perms permissions)
{
    auto check = [permissions](std::filesystem::perms bit, char c) 
    { 
        return (permissions & bit) == std::filesystem::perms::none ? '-' : c; 
    };

    return { check(std::filesystem::perms::owner_read , 'r'),
             check(std::filesystem::perms::owner_write, 'w'),
             check(std::filesystem::perms::owner_exec , 'x') };
}

// =================================================================================================

[[nodiscard]] std::size_t directory_size(const std::filesystem::path & path)
{
	std::size_t size = 0;

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

// =================================================================================================

[[nodiscard]] std::string entry_size(const std::filesystem::directory_entry & entry)
{
    std::size_t size{};

    if (std::filesystem::is_regular_file(entry.status()))
    {
        size = std::filesystem::file_size(entry);
    }
    else
    {
        size = directory_size(entry.path());
    }

    std::stringstream sout;

         if (size >= 1'073'741'824) { sout << (size / 1'073'741'824) << 'G'; } 
    else if (size >= 1'048'576    ) { sout << (size / 1'048'576    ) << 'M'; } 
    else if (size >= 1'024        ) { sout << (size / 1'024        ) << 'K'; } 
    else                            { sout << (size                ) << 'B'; }
    
    return sout.str();
}

// =================================================================================================

void view_directory(const std::filesystem::path & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		for (const auto & entry : std::filesystem::directory_iterator(path))
		{
            std::cout << entry_type       (entry.status()              ) << " | ";
            std::cout << entry_permissions(entry.status().permissions()) << " | ";

            std::cout << std::setw(5) << std::right << std::setfill(' ') << entry_size(entry) << " | ";

            std::cout << std::chrono::floor < std::chrono::seconds > (
                std::chrono::file_clock::to_sys(entry.last_write_time())) << " | ";

			std::cout << entry.path().filename().string() << std::endl;
		}
	}
}

// =================================================================================================

int main()
{
	view_directory(std::filesystem::current_path());

	return 0;
}