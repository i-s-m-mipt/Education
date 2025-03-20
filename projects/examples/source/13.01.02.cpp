#include <cassert>
#include <exception>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>

///////////////////////////////////////////////////////////

int main()
{
    std::stringstream stream("1 2 3 4 5 a");

//  -------------------------------------------------------

    auto state = stream.exceptions();

//  -------------------------------------------------------

    stream.exceptions(std::ios::eofbit | std::ios::badbit);

//  -------------------------------------------------------

    try
    {
        auto x = 0;

    //  -------------------------------------------

        assert(stream.good()); while (stream >> x);

        assert(stream.fail());

    //  -------------------------------------------

        stream.clear();

    //  -------------------------------------------

        assert(stream.get() == 'a');
    }
    catch (const std::ios_base::failure & exception)
    {
        assert(stream.eof() || stream.bad());

        std::cerr << "main : " << exception.what() << '\n';
    }

//  -------------------------------------------------------

    stream.exceptions(state);
}