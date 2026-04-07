////////////////////////////////////////////////////////////

// chapter : Streams

////////////////////////////////////////////////////////////

// section : Streams

////////////////////////////////////////////////////////////

// content : Streams
//
// content : Base Class std::ios_base
//
// content : State Flags
//
// content : Base Class std::basic_ios
//
// content : Flags std::ios::eofbit and std::ios::failbit
//
// content : Exception std::ios_base::failure
//
// content : Stream Buffers
//
// content : Buffer std::basic_streambuf
//
// content : Stream std::basic_istream
//
// content : Stream std::cin
//
// content : Stream std::basic_ostream
//
// content : Streams std::cout, std::clog and std::cerr
//
// content : Stream std::basic_iostream

////////////////////////////////////////////////////////////

#include <cassert>
#include <ios>
#include <iostream>
#include <sstream>

////////////////////////////////////////////////////////////

int main()
{
    std::stringstream stream("1 2 3 4 5 a");

//  --------------------------------------------------------

    auto state = stream.exceptions();

//  --------------------------------------------------------

    stream.exceptions(std::ios::eofbit | std::ios::failbit);

//  --------------------------------------------------------

    assert(stream.good());

//  --------------------------------------------------------

    try
    {
        auto x = 0;

    //  --------------------

        while (stream >> x);
    }
    catch (std::ios_base::failure const & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';

    //  ---------------------------------------------------

        assert(stream.fail()); stream.clear();

        assert(stream.good());

    //  ---------------------------------------------------

        assert(stream.get() == 'a');
    }

//  --------------------------------------------------------

    stream.exceptions(state);
}

////////////////////////////////////////////////////////////