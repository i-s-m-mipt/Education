#include <cassert>
#include <format>
#include <iterator>
#include <string>
#include <string_view>

//  ================================================================================================

struct Entity 
{ 
    int data_1 = 0; std::string data_2;
};

//  ================================================================================================

template <> struct std::formatter < Entity > : public std::formatter < std::string_view >
{
    auto format(const Entity & entity, std::format_context & context) const
    {
        std::string buffer;

        std::format_to(std::back_inserter(buffer), "{}, \"{}\"", entity.data_1, entity.data_2);
        
        return std::formatter < std::string_view > ::format("{ " + buffer + " }", context);
    }
};

//  ================================================================================================

int main()
{
    auto x = 1, y = 2;

    assert(std::format("x = {}", x) == "x = 1");

    std::string buffer;

    std::format_to(std::back_inserter(buffer), "y = {}", y);

    assert(buffer == "y = 2");

    assert(std::format("x = {0}, y = {1}", x, y) == "x = 1, y = 2");

//  ================================================================================================

    assert(std::format("{: <3}", x) == "1  ");
    assert(std::format("{: ^3}", x) == " 1 ");
    assert(std::format("{: >3}", x) == "  1");
    
    assert(std::format("{:03b}", x) == "001");
    assert(std::format("{:03o}", x) == "001");
    assert(std::format("{:03d}", x) == "001");
    assert(std::format("{:03x}", x) == "001");

//  ================================================================================================

    assert(std::format("{:.6}", 0.123'456'789) == "0.123457");

//  ================================================================================================

    assert(std::format("entity = {}", Entity(1, "entity")) == "entity = { 1, \"entity\" }");
}