/////////////////////////////////////////////////////////////////////////////////

// chapter : Distributed Network Systems

/////////////////////////////////////////////////////////////////////////////////

// content : Websocket Protocol
//
// content : Library Boost.Beast

/////////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <print>
#include <string_view>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

/////////////////////////////////////////////////////////////////////////////////

#include <openssl/ssl.h>

/////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    boost::asio::io_context context_1;

//  -----------------------------------------------------------------------------

    boost::asio::ssl::context context_2(boost::asio::ssl::context::tls_client);

//  -----------------------------------------------------------------------------

    context_2.set_default_verify_paths();

//  -----------------------------------------------------------------------------

    context_2.set_verify_mode(boost::asio::ssl::verify_peer);

//  -----------------------------------------------------------------------------

    boost::beast::websocket::stream
    <
        boost::beast::ssl_stream < boost::beast::tcp_stream >
    >
    stream_1(context_1, context_2);

//  -----------------------------------------------------------------------------

    auto & stream_2 = stream_1.next_layer();

    auto & stream_3 = stream_2.next_layer();

//  -----------------------------------------------------------------------------

    auto host = "stream.binance.com";

//  -----------------------------------------------------------------------------

    stream_2.set_verify_callback(boost::asio::ssl::host_name_verification(host));

//  -----------------------------------------------------------------------------

    SSL_set_tlsext_host_name(stream_2.native_handle(), host);

//  -----------------------------------------------------------------------------

    stream_3.connect(resolve(host, "443"));

//  -----------------------------------------------------------------------------

    stream_2.handshake(boost::asio::ssl::stream_base::client);

//  -----------------------------------------------------------------------------

    stream_1.handshake(host, "/ws/btcusdt@bookTicker");

//  -----------------------------------------------------------------------------

    boost::beast::flat_buffer buffer;

//  -----------------------------------------------------------------------------

    for (auto i = 0uz; i < 5; ++i)
    {
        stream_1.read(buffer);

    //  ----------------------------------------------------------------

        auto frame = boost::beast::buffers_to_string(std::data(buffer));

    //  ----------------------------------------------------------------

        std::print("main : frame = {}\n", frame);

    //  ----------------------------------------------------------------

        buffer.consume(std::size(buffer));
    }

//  -----------------------------------------------------------------------------

    boost::system::error_code error;

//  -----------------------------------------------------------------------------

    stream_1.close(boost::beast::websocket::close_code::normal, error);
}

/////////////////////////////////////////////////////////////////////////////////