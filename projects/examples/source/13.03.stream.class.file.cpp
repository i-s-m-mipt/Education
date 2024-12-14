#include <bit>
#include <cassert>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <streambuf>
#include <string>

//  ================================================================================================

class Redirector
{
public:

    explicit Redirector(const std::string & path) : m_fout(path, std::ios::out)
    {
        if (m_fout) 
        {
            m_buffer = std::cout.rdbuf(m_fout.rdbuf());
        }
        else 
        {
            throw std::runtime_error("invalid stream");
        }
    }

   ~Redirector() 
    { 
        if (m_buffer) 
        {
            std::cout.rdbuf(m_buffer); 
        }
    }

private:

    std::fstream m_fout; std::streambuf * m_buffer = nullptr;
};

//  ================================================================================================

struct Entity 
{ 
    int data_1 = 0; std::string data_2; 
};

//  ================================================================================================

auto & operator>>(std::ifstream & fin, Entity & entity)
{
    fin.read(std::bit_cast < char * > (&entity.data_1), sizeof(entity.data_1));

    auto size = 0uz;

    fin.read(std::bit_cast < char * > (&size), sizeof(size));

    entity.data_2.resize(size);

    fin.read(std::bit_cast < char * > (&entity.data_2.front()), size);

    return fin;
}

//  ================================================================================================

auto & operator<<(std::ofstream & fout, const Entity & entity)
{
    fout.write(std::bit_cast < char * > (&entity.data_1), sizeof(entity.data_1));

    auto size = std::size(entity.data_2);

    fout.write(std::bit_cast < char * > (&size), sizeof(size));

    fout.write(std::data(entity.data_2), std::size(entity.data_2));

    return fout;
}

//  ================================================================================================

int main()
{
    auto path = "13.03.stream.class.file.example.data";

    auto size = 5uz;

//  ================================================================================================

    if (std::fstream fout(path, std::ios::out); fout)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            fout << std::string(size, 'a') << std::endl;
        }

        fout.seekp(2 * (size + 1), std::ios::beg);

        fout << "bbbbb";
    }
    else 
    {
        throw std::runtime_error("invalid stream");
    }

//  ================================================================================================

    if (std::fstream fin(path, std::ios::in); fin)
    {
        fin.seekg(2 * (size + 1), std::ios::beg);

        std::string input; std::getline(fin, input); assert(input == "bbbbb");

        fin.seekg(0, std::ios::end); 

        assert(static_cast < std::size_t > (fin.tellg()) == size * (size + 1));
    }
    else 
    {
        throw std::runtime_error("invalid stream");
    }

//  ================================================================================================

    std::cout << "Enter any character to continue : "; char c; std::cin >> c;

    std::filesystem::remove(path);
}