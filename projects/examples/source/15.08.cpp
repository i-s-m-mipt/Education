//////////////////////////////////////////////////////////////

// chapter : Distributed Network Systems

//////////////////////////////////////////////////////////////

// content : Synchronous Client
//
// content : Localhost
//
// content : Algorithm std::ranges::fill

//////////////////////////////////////////////////////////////

#include <algorithm>
#include <array>
#include <cassert>

//////////////////////////////////////////////////////////////

#include <boost/asio.hpp>

//////////////////////////////////////////////////////////////

int main()
{
    boost::asio::io_context context;

//  ----------------------------------------------------------

    boost::asio::ip::tcp::socket socket(context);

//  ----------------------------------------------------------

    auto address = boost::asio::ip::make_address("127.0.0.1");

//  ----------------------------------------------------------

    boost::asio::ip::tcp::endpoint endpoint(address, 80);

//  ----------------------------------------------------------

    socket.connect(endpoint);

//  ----------------------------------------------------------

    std::array < char, 1 << 10 > array = {};

//  ----------------------------------------------------------

    std::ranges::fill(array, 'a');

//  ----------------------------------------------------------

    boost::asio::write(socket, boost::asio::buffer(array));

    boost::asio::read (socket, boost::asio::buffer(array));

//  ----------------------------------------------------------

    auto lambda = [](auto x){ assert(x == 'a'); };

//  ----------------------------------------------------------

    std::ranges::for_each(array, lambda);
}

//////////////////////////////////////////////////////////////