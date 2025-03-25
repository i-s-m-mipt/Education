#include <cassert>
#include <exception>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdexcept>

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
    catch (const std::ios_base::failure & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';

    //  ---------------------------------------------------

        assert(stream.fail());

    //  ---------------------------------------------------

        stream.clear();

    //  ---------------------------------------------------

        assert(stream.good() && stream.get() == 'a');
    }

//  --------------------------------------------------------

    stream.exceptions(state);
}