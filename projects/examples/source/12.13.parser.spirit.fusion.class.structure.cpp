#include <exception>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std::literals;

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>

#include <gtest/gtest.h>

//  ================================================================================================

struct System { std::string name; int data{}; }; 

//  ================================================================================================

[[nodiscard]] bool operator==(const System & lhs, const System & rhs) noexcept
{
    return 
    (
        lhs.name == rhs.name && 
        lhs.data == rhs.data
    );
}

//  ================================================================================================

BOOST_FUSION_ADAPT_STRUCT(System, name, data)

//  ================================================================================================

namespace parser
{
    const boost::spirit::x3::rule < struct rule_tag, System > rule;
    
    const auto name_def = boost::spirit::x3::lexeme
    [
        '"' 
            >> *(boost::spirit::x3::char_ - '"') >> 
        '"'
    ];

    const auto data_def = boost::spirit::x3::int_;

    const auto rule_def = 
    (
        '{' 
            >> name_def >> ',' 
            >> data_def >> 
        '}'
    );

    BOOST_SPIRIT_DEFINE(rule);
}

//  ================================================================================================

[[nodiscard]] System test(std::string_view data)
{
    System system;

    const auto skip = boost::spirit::x3::ascii::space;

    boost::spirit::x3::phrase_parse(std::cbegin(data), std::cend(data), parser::rule, skip, system);

    return system;
}

//  ================================================================================================

TEST(Parser, System)
{
    ASSERT_EQ(test(R"({ "system", 1 })"), System("system", 1));
}

//  ================================================================================================

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}