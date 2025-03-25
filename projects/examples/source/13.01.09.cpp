#include <exception>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <streambuf>
#include <string>

/////////////////////////////////////////////////////////

class Adapter
{
public :

    Adapter(const std::string & path) : m_stream(path)
    {
        if (m_stream) 
        {
            m_buffer = std::cout.rdbuf(m_stream.rdbuf());
        }
    }

   ~Adapter() 
    { 
        if (m_buffer) 
        {
            std::cout.rdbuf(m_buffer);
        }
    }

private :

    std::fstream m_stream;
    
    std::streambuf * m_buffer = nullptr;
};

/////////////////////////////////////////////////////////

int main()
{
    auto path = "13.01.09.data";

//  ----------------------------------------------------

    {
        Adapter adapter(path);

    //  ----------------------
            
        std::cout << "main\n";
    }

//  ----------------------------------------------------

    std::cout << "main : enter char : "; std::cin.get();

//  ----------------------------------------------------

    std::filesystem::remove(path);
}