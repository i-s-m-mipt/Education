/////////////////////////////////////////////////////////////////////

// chapter : Input and Output Subsystems

/////////////////////////////////////////////////////////////////////

// content : Underlying Buffers
//
// content : Buffer std::streambuf

/////////////////////////////////////////////////////////////////////

// support : Boost.IOStreams

/////////////////////////////////////////////////////////////////////

#include <filesystem>
#include <fstream>
#include <iostream>
#include <print>
#include <streambuf>
#include <string>

/////////////////////////////////////////////////////////////////////

class Adapter
{
public :

    Adapter(std::string const & path) : m_stream(path, std::ios::out)
    {
        m_streambuf = std::cout.rdbuf(m_stream.rdbuf());
    }

//  -----------------------------------------------------------------

   ~Adapter()
    {
        std::cout.rdbuf(m_streambuf);
    }

private :

    std::fstream m_stream;

    std::streambuf * m_streambuf = nullptr;
};

/////////////////////////////////////////////////////////////////////

int main()
{
    auto path = "output.data";

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

/////////////////////////////////////////////////////////////////////