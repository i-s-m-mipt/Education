#include <cassert>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class Redirector // good: RAII wrapper to for redirecting cout buffer to file buffer
{
public:

    explicit Redirector (const std::string & file) : fout(file, std::ios::out)
    {
        if (fout) m_old_buffer = std::cout.rdbuf(fout.rdbuf());
    }

   ~Redirector() noexcept 
    { 
        try { if (m_old_buffer) std::cout.rdbuf(m_old_buffer); } catch(...) { std::abort(); } 
    }

private:

    std::fstream fout;

    std::streambuf * m_old_buffer;

}; // class Redirector

int main()
{
    constexpr auto file = "13.03.stream.class.file.example.data";

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

    std::cout << "Enter any character to continue: "; char c{}; std::cin >> c;

    std::filesystem::remove(file);

    return 0;
}