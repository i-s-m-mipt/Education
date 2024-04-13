#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    constexpr auto file = "example.data";

    constexpr std::size_t size = 5;

    {
        std::fstream fout(file, std::ios::out); // note: RAII idiom

        for (std::size_t i = 0; i < size; ++i)
        {
            fout << std::string(size, 'a' + i) << std::endl;
        }

        fout.seekp(2 * (size + 1), std::ios::beg); // note: remember EOL

        fout << "hello"; // note: rewrites existing characters in file
    }

    if (std::fstream fin(file, std::ios::in); fin)
    {
        fin.seekg(2 * (size + 1), std::ios::beg);

        std::string input; std::getline(fin, input); assert(input == "hello");
    }
    else std::cerr << "invalid file stream\n";

    return 0;
}