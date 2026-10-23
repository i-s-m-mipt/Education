//////////////////////////////////////////////////////////////////////////////////////////

// chapter : Distributed Network Systems

//////////////////////////////////////////////////////////////////////////////////////////

// content : Domain Name System (DNS)
//
// content : Library Boost.Asio

//////////////////////////////////////////////////////////////////////////////////////////

#include <print>
#include <string_view>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////////////

#include <boost/asio.hpp>

//////////////////////////////////////////////////////////////////////////////////////////

#include "08.34.hpp"

//////////////////////////////////////////////////////////////////////////////////////////

auto resolve(std::string_view host, std::string_view port)
{
    boost::asio::io_context context;

    boost::asio::ip::tcp::resolver resolver(context);

    std::vector < boost::asio::ip::tcp::endpoint > endpoints;

    for (auto const & result : resolver.resolve(host, port))
    {
        if (auto endpoint = result.endpoint(); endpoint.address().is_v4())
        {
            endpoints.push_back(endpoint);
        }
    }

    return endpoints;
}

//////////////////////////////////////////////////////////////////////////////////////////

void ping(std::vector < boost::asio::ip::tcp::endpoint > const & endpoints)
{
    boost::asio::io_context context;

    for (auto const & endpoint : endpoints)
    {
        auto address = endpoint.address().to_string();

        try
        {
            boost::asio::ip::tcp::socket socket(context);

            socket.open(endpoint.protocol());

            Timer timer;

            socket.connect(endpoint);

            auto latency = timer.elapsed().count();

            std::print("ping : address = {:15} latency = {:.6f} (s)\n", address, latency);
        }
        catch (boost::system::system_error const &)
        {
            std::print("ping : address = {:15} latency = inf\n", address);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    ping(resolve("fstream.binance.com", "443"));
}

//////////////////////////////////////////////////////////////////////////////////////////