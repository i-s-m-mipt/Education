#include <cassert>
#include <format>

/////////////////////////////////////////////////////////////

int main()
{
    assert(std::format("{:#b}", 0b11111111) == "0b11111111");

    assert(std::format("{:#o}", 0377      ) == "0377"      );

    assert(std::format("{:#d}", 255       ) == "255"       );

    assert(std::format("{:#x}", 0xff      ) == "0xff"      );
}