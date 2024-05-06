#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>

//  ================================================================================================

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

//  ================================================================================================

[[nodiscard]] std::string entry_permissions(std::filesystem::perms permissions)
{
    auto verify = [permissions](auto bit, auto c) constexpr noexcept 
    { 
        return (permissions & bit) == std::filesystem::perms::none ? '-' : c; 
    };

    return { verify(std::filesystem::perms::owner_read , 'r'),
             verify(std::filesystem::perms::owner_write, 'w'),
             verify(std::filesystem::perms::owner_exec , 'x') };
}

//  ================================================================================================

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

//  ================================================================================================

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

    sout << std::setw(5) << std::right << std::setfill(' ');

         if (size >= 1'073'741'824) { sout << (size / 1'073'741'824) << 'G'; } 
    else if (size >= 1'048'576    ) { sout << (size / 1'048'576    ) << 'M'; } 
    else if (size >= 1'024        ) { sout << (size / 1'024        ) << 'K'; } 
    else                            { sout << (size                ) << 'B'; }
    
    return sout.str();
}

//  ================================================================================================

void view_directory(const std::filesystem::path & path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
        constexpr auto separator = " | ";

		for (const auto & entry : std::filesystem::directory_iterator(path))
		{
            std::cout << entry_type       (entry.status()              ) << separator;
            std::cout << entry_permissions(entry.status().permissions()) << separator;

            std::cout << entry_size(entry) << separator;

            const auto time_point = std::chrono::file_clock::to_sys(entry.last_write_time());

            std::cout << std::chrono::floor < std::chrono::seconds > (time_point) << separator;

			std::cout << entry.path().filename().string() << std::endl;
		}
	}
}

//  ================================================================================================

int main()
{
	view_directory(std::filesystem::current_path());

	return 0;
}