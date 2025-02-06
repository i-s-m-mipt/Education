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

    auto rule_def = '{' >> boost::spirit::x3::int_ >> boost::spirit::x3::int_ >> '}';

    BOOST_SPIRIT_DEFINE(rule);
}

//////////////////////////////////////////////////////////////////////////////////////////

auto parse(std::string_view view)
{
    auto begin = std::begin(view), end = std::end(view);

    auto space = boost::spirit::x3::ascii::space;

    Entity entity;

    auto state = boost::spirit::x3::phrase_parse(begin, end, parser::rule, space, entity);

    if (!state || begin != end)
    {
        throw std::runtime_error("invalid view");
    }

    return entity;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto entity = parse(R"({ 1 1 })");

    assert(entity.data_1 == 1);
    
    assert(entity.data_2 == 1);
}