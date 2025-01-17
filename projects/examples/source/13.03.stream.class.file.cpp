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

///////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
    int data_1 = 0; std::string data_2; 
};

///////////////////////////////////////////////////////////////////////////////////////////////

auto & operator>>(std::istream & stream, Entity & entity)
{
    stream.read(std::bit_cast < char * > (&entity.data_1), sizeof(entity.data_1));

    auto size = 0uz;

    stream.read(std::bit_cast < char * > (&size), sizeof(size));

    entity.data_2.resize(size);

    stream.read(std::bit_cast < char * > (&entity.data_2.front()), size);

    return stream;
}

///////////////////////////////////////////////////////////////////////////////////////////////

auto & operator<<(std::ostream & stream, const Entity & entity)
{
    stream.write(std::bit_cast < char * > (&entity.data_1), sizeof(entity.data_1));

    auto size = std::size(entity.data_2);

    stream.write(std::bit_cast < char * > (&size), sizeof(size));

    stream.write(std::data(entity.data_2), std::size(entity.data_2));

    return stream;
}

///////////////////////////////////////////////////////////////////////////////////////////////

class Redirector
{
public:

    Redirector(const std::string & path) : m_stream(path, std::ios::out)
    {
        if (m_stream) 
        {
            m_buffer = std::cout.rdbuf(m_stream.rdbuf());
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

    std::fstream m_stream; std::streambuf * m_buffer = nullptr;
};

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        if (std::fstream stream("13.03.stream.class.file.example.data", std::ios::out); stream)
        {
            auto size = 5uz;

            for (auto i = 0uz; i < size; ++i)
            {
                stream << std::string(size, 'a') << '\n';
            }

            stream.seekp((size - 1) * (size + 1), std::ios::beg);

            stream << "bbbbb\n" << Entity(1, "aaaaa") << '\n';
        }
        else 
        {
            throw std::runtime_error("invalid stream");
        }

        std::cout << "main : enter char to continue : "; char c; std::cin >> c;
    }

//  -------------------------------------------------------------------------------------------

    {
        if (std::fstream stream("13.03.stream.class.file.example.data", std::ios::in); stream)
        {
            auto size = 5uz;

            stream.seekg((size - 1) * (size + 1), std::ios::beg);

            std::string input; std::getline(stream, input); 
            
            assert(input == "bbbbb");

            Entity entity; stream >> entity;

            assert(entity.data_1 == 1 && entity.data_2 == "aaaaa");
        }
        else 
        {
            throw std::runtime_error("invalid stream");
        }
    }

//  -------------------------------------------------------------------------------------------

    {
        {
            Redirector redirector("13.03.stream.class.file.example.data"); 
            
            std::cout << "main : trace\n";
        }

        std::cout << "main : enter char to continue : "; char c; std::cin >> c;
    }

//  -------------------------------------------------------------------------------------------

    {
        std::filesystem::remove("13.03.stream.class.file.example.data");
    }
}