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

        std::format_to(std::back_inserter(buffer), "{}, \"{}\"", entity.data_1, entity.data_2);
        
        return std::formatter < std::string_view > ::format("{ " + buffer + " }", context);
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(std::format("{0}, {1}", false, true) == "false, true");

//  ----------------------------------------------------------------------------------------

    auto x = 1, y = 2;

    assert(std::format("x = {}", x) == "x = 1");

    std::string buffer;

    std::format_to(std::back_inserter(buffer), "y = {}", y);

    assert(buffer == "y = 2");

//  ----------------------------------------------------------------------------------------

    assert(std::format("{: <+6}", x) == "+1    ");
    assert(std::format("{: ^+6}", x) == "  +1  ");
    assert(std::format("{: >+6}", x) == "    +1");

//  ----------------------------------------------------------------------------------------
    
    assert(std::format("{:#06b}", x) == "0b0001");
    assert(std::format("{:#06o}", x) == "000001");
    assert(std::format("{:#06d}", x) == "000001");
    assert(std::format("{:#06x}", x) == "0x0001");

//  ----------------------------------------------------------------------------------------

    assert(std::format("{:8.6f}", 0.123'456'789) == "0.123457");

//  ----------------------------------------------------------------------------------------

    assert(std::format("entity = {}", Entity(1, "entity")) == "entity = { 1, \"entity\" }");
}