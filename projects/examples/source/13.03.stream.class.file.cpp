#include <bit>
#include <cassert>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

//  ================================================================================================

class Redirector
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

//  ================================================================================================

struct S { char c{}; int i{}; std::string s; };

//  ================================================================================================

std::ofstream & operator<<(std::ofstream & fout, const S & s) // note: см. std::ios::binary
{
    fout.write(&s.c, sizeof(s.c));

    fout.write(std::bit_cast < const char * > (&s.i), sizeof(s.i));

    const auto size = std::size(s.s);

    fout.write(std::bit_cast < const char * > (&size), sizeof(size));

    fout.write(std::data(s.s), std::size(s.s));

    return fout;
}

//  ================================================================================================

std::ifstream & operator>>(std::ifstream & fin, S & s) // note: см. std::ios::binary
{
    fin.read(&s.c, sizeof(s.c));

    fin.read(std::bit_cast < char * > (&s.i), sizeof(s.i));

    std::size_t size = 0;

    fin.read(std::bit_cast < char * > (&size), sizeof(size));

    s.s.resize(size);

    fin.read(std::bit_cast < char * > (&s.s.front()), size);

    return fin;
}

//  ================================================================================================

int main()
{
    constexpr auto file = "13.03.stream.class.file.example.data";

    constexpr std::size_t size = 5;

//  ================================================================================================

    {
        std::fstream fout(file, std::ios::out);

        for (std::size_t i = 0; i < size; ++i)
        {
            fout << std::string(size, 'a' + i) << std::endl;
        }

        fout.seekp(2 * (size + 1), std::ios::beg); // note: см. CRLF на Windows

        fout << "hello";
    }

//  ================================================================================================

    if (std::fstream fin(file, std::ios::in); fin)
    {
        fin.seekg(2 * (size + 1), std::ios::beg);

        std::string input; std::getline(fin, input); assert(input == "hello");

        fin.seekg(0, std::ios::end); 

        assert(fin.tellg() == size * (size + 1));
    }
    else std::cerr << "invalid file stream\n";

//  ================================================================================================

    std::cout << "Enter any character to continue: "; char c{}; std::cin >> c;

    std::filesystem::remove(file);

    return 0;
}