#include <cassert>
#include <exception>
#include <iterator>
#include <stdexcept>
#include <string_view>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>

/////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
    int x = 0, y = 0;
};

/////////////////////////////////////////////////////////////////////////////////////

BOOST_FUSION_ADAPT_STRUCT(Entity, x, y)

/////////////////////////////////////////////////////////////////////////////////////

namespace parser
{
    boost::spirit::x3::rule < struct rule_tag, Entity > rule;

    auto rule_def = '{' >> boost::spirit::x3::int_ >> boost::spirit::x3::int_ >> '}';

    BOOST_SPIRIT_DEFINE(rule);
}

/////////////////////////////////////////////////////////////////////////////////////

auto parse(std::string_view view)
{
    auto begin = std::begin(view), end = std::end(view);

    auto space = boost::spirit::x3::ascii::space;

    Entity entity;

    boost::spirit::x3::phrase_parse(begin, end, parser::rule, space, entity);

    return entity;
}

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto entity = parse(R"({ 1 1 })");

//  ----------------------------------

    assert(entity.x == 1);
    
    assert(entity.y == 1);
}