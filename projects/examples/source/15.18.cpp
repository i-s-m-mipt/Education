////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cstdio>
#include <format>
#include <iterator>
#include <print>
#include <regex>
#include <string>

////////////////////////////////////////////////////////////////////////////////////

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////////////////////////////////

class Pipe : private boost::noncopyable
{
public :

    Pipe(std::FILE * stream) : m_stream(stream) {}

//  ----------------------------------------------

   ~Pipe()
    {
        pclose(m_stream);
    }

//  ----------------------------------------------

    auto get() const
    {
        return m_stream;
    }

private :

    std::FILE * m_stream = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    boost::asio::io_context io_context;

//  --------------------------------------------------------------------------------

    boost::asio::ip::tcp::resolver resolver(io_context);

//  --------------------------------------------------------------------------------

    for (auto const & result : resolver.resolve("google.com", "https"))
    {
        auto address = result.endpoint().address().to_string();

    //  ----------------------------------------------------------------------------

        Pipe pipe(popen(std::format("nmap {} -p {}", address, 80).c_str(), "r"));

    //  ----------------------------------------------------------------------------

        std::array < char, 1 << 10 > array = {};

    //  ----------------------------------------------------------------------------

        std::string string;

    //  ----------------------------------------------------------------------------

        while (fgets(std::begin(array), std::size(array), pipe.get()))
        {
            string += std::data(array);
        }

    //  ----------------------------------------------------------------------------

        std::smatch matches;

    //  ----------------------------------------------------------------------------

        std::regex_search(string, matches, std::regex(R"(([0-9.]+)s)"));

    //  ----------------------------------------------------------------------------

        auto latency = std::stod(matches[1]);

    //  ----------------------------------------------------------------------------

        std::print("main : address = {}, latency = {:.6f} (s)\n", address, latency);
    }
}

////////////////////////////////////////////////////////////////////////////////////