#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    constexpr auto file = "example.data"; // note: consider std::filesystem::path

    constexpr std::size_t size = 5;

    {
        std::fstream fout(file, std::ios::out); // note: open-close by RAII idiom

        for (std::size_t i = 0; i < size; ++i)
        {
            fout << std::string(size, 'a' + i) << std::endl;
        }

        fout.seekp(2 * (size + 1), std::ios::beg); // note: CR and LF for Windows

        fout << "hello"; // note: rewrites file
    }

    if (std::fstream fin(file, std::ios::in); fin)
    {
        fin.seekg(2 * (size + 1), std::ios::beg); // note: consider binary mode

        std::string input; std::getline(fin, input); assert(input == "hello");

        fin.seekg(0, std::ios::end); 

        assert(fin.tellg() == size * (size + 1));
    }
    else std::cerr << "invalid file stream\n";

    return 0;
}