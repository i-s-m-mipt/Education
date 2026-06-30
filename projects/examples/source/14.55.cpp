////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

////////////////////////////////////////////////////////////////////////////////

// content : Argument Parser
//
// content : Library Boost.ProgramOptions

////////////////////////////////////////////////////////////////////////////////

// support : ./14.55 --option_x 1 -y 2

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <print>

////////////////////////////////////////////////////////////////////////////////

#include <boost/program_options.hpp>

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
    boost::program_options::options_description description("description");

//  ----------------------------------------------------------------------------

    auto x = 0, y = 0;

//  ----------------------------------------------------------------------------

    description.add_options()

        ("option_x,x", boost::program_options::value < int > (&x), "x")

        ("option_y,y", boost::program_options::value < int > (&y), "y");

//  ----------------------------------------------------------------------------

    std::cout << description << '\n';

//  ----------------------------------------------------------------------------

    boost::program_options::variables_map map;

//  ----------------------------------------------------------------------------

    boost::program_options::store
    (
        boost::program_options::parse_command_line(argc, argv, description), map
    );

//  ----------------------------------------------------------------------------

    boost::program_options::notify(map);

//  ----------------------------------------------------------------------------

    if (map.contains("option_x")) { std::print("main : x = {}\n", x); }

    if (map.contains("option_y")) { std::print("main : y = {}\n", y); }
}

////////////////////////////////////////////////////////////////////////////////