#include <cassert>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string_view>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>

//////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
    int data_1 = 0, data_2 = 0; 
};

BOOST_FUSION_ADAPT_STRUCT(Entity, data_1, data_2)

//////////////////////////////////////////////////////////////////////////////////////////

namespace parser
{
    boost::spirit::x3::rule < struct rule_tag, Entity > rule;

    auto rule_def = 
    (
        '{' >> boost::spirit::x3::int_ >> boost::spirit::x3::int_ >> '}'
    );

    BOOST_SPIRIT_DEFINE(rule);
}

//////////////////////////////////////////////////////////////////////////////////////////

auto parse(std::string_view data)
{
    auto begin = std::begin(data), end = std::end(data);

    auto skip = boost::spirit::x3::ascii::space;

    Entity entity(0, 0);

    auto result = boost::spirit::x3::phrase_parse(begin, end, parser::rule, skip, entity);

    if (!result || begin != end)
    {
        throw std::runtime_error("invalid data");
    }

    return entity;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto entity = parse(R"({ 1 2 })");

    assert(entity.data_1 == 1 && entity.data_2 == 2);
}