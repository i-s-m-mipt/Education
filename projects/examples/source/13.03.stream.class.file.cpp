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

///////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
    int data_1 = 0; std::string data_2; 
};

///////////////////////////////////////////////////////////////////////////////////

auto & operator>>(std::istream & stream, Entity & entity)
{
    stream.read(std::bit_cast < char * > (&entity.data_1), sizeof(entity.data_1));

    auto size = 0uz;

    stream.read(std::bit_cast < char * > (&size), sizeof(size));

    entity.data_2.resize(size);

    stream.read(std::bit_cast < char * > (&entity.data_2.front()), size);

    return stream;
}

///////////////////////////////////////////////////////////////////////////////////

auto & operator<<(std::ostream & stream, const Entity & entity)
{
    stream.write(std::bit_cast < char * > (&entity.data_1), sizeof(entity.data_1));

    auto size = std::size(entity.data_2);

    stream.write(std::bit_cast < char * > (&size), sizeof(size));

    stream.write(std::data(entity.data_2), std::size(entity.data_2));

    return stream;
}

///////////////////////////////////////////////////////////////////////////////////

class Redirector
{
public:

    Redirector(const std::string & path) : m_fout(path, std::ios::out)
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

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto path = "13.03.stream.class.file.example.data";

    auto size = 5uz;

//  ---------------------------------------------------------------------------

    if (std::fstream fout(path, std::ios::out); fout)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            fout << std::string(size, 'a') << '\n';
        }

        fout.seekp((size - 1) * (size + 1), std::ios::beg);

        fout << "bbbbb\n" << Entity(1, "aaaaa");
    }
    else 
    {
        throw std::runtime_error("invalid stream");
    }

//  ---------------------------------------------------------------------------

    if (std::fstream fin(path, std::ios::in); fin)
    {
        fin.seekg((size - 1) * (size + 1), std::ios::beg);

        std::string input; std::getline(fin, input); 
        
        assert(input == "bbbbb");

        Entity entity; fin >> entity;

        assert(entity.data_1 == 1 && entity.data_2 == "aaaaa");
    }
    else 
    {
        throw std::runtime_error("invalid stream");
    }

    std::cout << "main : enter any character to continue : "; char c1; std::cin >> c1;

//  ---------------------------------------------------------------------------

    {
        Redirector redirector(path); std::cout << "main : trace\n";
    }

    std::cout << "main : enter any character to continue : "; char c2; std::cin >> c2;

//  ---------------------------------------------------------------------------

    std::filesystem::remove(path);
}