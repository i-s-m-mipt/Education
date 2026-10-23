/////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Distributed Network Systems

/////////////////////////////////////////////////////////////////////////////////////////////////

// content : HyperText Transfer Protocol (HTTP)
//
// content : Library Boost.Beast

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <print>
#include <string_view>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////

#include <openssl/ssl.h>

/////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////

auto make_request(std::string_view host, std::string_view target)
{
    boost::beast::http::request < boost::beast::http::empty_body > request;

    request.method(boost::beast::http::verb::get);

    request.target(target);

    request.version(11);

    request.set(boost::beast::http::field::host, host);

    request.set(boost::beast::http::field::user_agent, "15.18");

    request.set(boost::beast::http::field::accept, "application/json");

    request.keep_alive(false);

    return request;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    boost::asio::  io_context context_1;

    boost::asio::ssl::context context_2(boost::asio::ssl::context::tls_client);

//  ---------------------------------------------------------------------------------------------

    context_2.set_default_verify_paths();

//  ---------------------------------------------------------------------------------------------

    context_2.set_verify_mode(boost::asio::ssl::verify_peer);

//  ---------------------------------------------------------------------------------------------

    boost::beast::ssl_stream < boost::beast::tcp_stream > stream(context_1, context_2);

//  ---------------------------------------------------------------------------------------------

    auto host = "data-api.binance.vision";

//  ---------------------------------------------------------------------------------------------

    stream.set_verify_callback(boost::asio::ssl::host_name_verification(host));

//  ---------------------------------------------------------------------------------------------

    SSL_set_tlsext_host_name(stream.native_handle(), host);

//  ---------------------------------------------------------------------------------------------

    boost::beast::get_lowest_layer(stream).connect(resolve(host, "443"));

//  ---------------------------------------------------------------------------------------------

    stream.handshake(boost::asio::ssl::stream_base::client);

//  ---------------------------------------------------------------------------------------------

    boost::beast::http::write(stream, make_request(host, "/api/v3/ticker/price?symbol=BTCUSDT"));

//  ---------------------------------------------------------------------------------------------

    boost::beast::flat_buffer buffer;

//  ---------------------------------------------------------------------------------------------

    boost::beast::http::response < boost::beast::http::string_body > response;

//  ---------------------------------------------------------------------------------------------

    boost::beast::http::read(stream, buffer, response);

//  ---------------------------------------------------------------------------------------------

    std::print("main : response = {}\n", response.body());

//  ---------------------------------------------------------------------------------------------

    stream.shutdown();
}

/////////////////////////////////////////////////////////////////////////////////////////////////