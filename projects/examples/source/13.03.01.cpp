#include <cassert>
#include <format>
#include <iterator>
#include <string>
#include <string_view>

///////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
    int x = 0;
    
    std::string string;
};

///////////////////////////////////////////////////////////////////////////////////////////

template <> class std::formatter < Entity > : public std::formatter < std::string_view >
{
public:

    auto format(const Entity & entity, std::format_context & context) const
    {
        std::string string;

        std::format_to(std::back_inserter(string), "{} {}", entity.x, entity.string);
        
        return std::formatter < std::string_view > ::format("{ " + string + " }", context);
    }
};

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(std::format("{0}, {1}", false, true) == "false, true");

//  ---------------------------------------------------------------

    std::string string;

//  ---------------------------------------------------------------

    std::format_to(std::back_inserter(string), "{}, {}", 1, 2);

//  ---------------------------------------------------------------

    assert(string == "1, 2");

//  ---------------------------------------------------------------

    assert(std::format("{:_>8}", 1) == "_______1");

//  ---------------------------------------------------------------

    assert(std::format("{:#x}", 1) == "0x1");

//  ---------------------------------------------------------------

    assert(std::format("{:.6f}", 1.0) == "1.000000");

//  ---------------------------------------------------------------

    assert(std::format("{:+.1e}", 1.0) == "+1.0e+00");

//  ---------------------------------------------------------------

    assert(std::format("{}", Entity(1, "aaaaa")) == "{ 1 aaaaa }");
}