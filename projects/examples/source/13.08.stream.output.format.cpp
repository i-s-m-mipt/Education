#include <cassert>
#include <format>
#include <iterator>
#include <string>
#include <string_view>

///////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
    int data_1 = 0; std::string data_2;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template <> class std::formatter < Entity > : public std::formatter < std::string_view >
{
public:

    auto format(const Entity & entity, std::format_context & context) const
    {
        std::string buffer;

        std::format_to(std::back_inserter(buffer), "{} {}", entity.data_1, entity.data_2);
        
        return std::formatter < std::string_view > ::format("{ " + buffer + " }", context);
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(std::format("{0}, {1}", false, true) == "false, true");

//  -----------------------------------------------------------------

    std::string buffer;

    std::format_to(std::back_inserter(buffer), "{}, {}", 1, 2);

    assert(buffer == "1, 2");

//  -----------------------------------------------------------------

    assert(std::format("{: <+6}", 1) == "+1    ");
    
    assert(std::format("{: ^+6}", 1) == "  +1  ");

    assert(std::format("{: >+6}", 1) == "    +1");

//  -----------------------------------------------------------------
    
    assert(std::format("{:#b}", 255) == "0b11111111");

    assert(std::format("{:#o}", 255) == "0377");

    assert(std::format("{:#d}", 255) == "255");

    assert(std::format("{:#x}", 255) == "0xff");

//  -----------------------------------------------------------------

    assert(std::format("{:8.6f}", 0.123'456'789) == "0.123457");

//  -----------------------------------------------------------------

    assert(std::format("{}", Entity(1, "aaaaa")) == "{ 1 aaaaa }");
}