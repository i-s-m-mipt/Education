#include <bit>
#include <cassert>
#include <cstddef>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
    int x = 0;
    
    std::string string;
};

////////////////////////////////////////////////////////////////////////

auto & operator>>(std::istream & stream, Entity & entity)
{
    auto size = 0uz;

//  -------------------------------------------------------------------

    stream.read(std::bit_cast < char * > (&entity.x), sizeof(int));

    stream.read(std::bit_cast < char * > (&size), sizeof(std::size_t));

//  -------------------------------------------------------------------

    entity.string.resize(size);

    stream.read(&entity.string.front(), size);

//  -------------------------------------------------------------------

    return stream;
}

////////////////////////////////////////////////////////////////////////

auto & operator<<(std::ostream & stream, const Entity & entity)
{
    auto size = std::size(entity.string);

//  --------------------------------------------------------------------

    stream.write(std::bit_cast < char * > (&entity.x), sizeof(int));

    stream.write(std::bit_cast < char * > (&size), sizeof(std::size_t));

//  --------------------------------------------------------------------

    stream.write(std::data(entity.string), std::size(entity.string));

//  --------------------------------------------------------------------

    return stream;
}

////////////////////////////////////////////////////////////////////////

int main()
{
    std::string string(sizeof(int) + sizeof(std::size_t), '\0');

//  ------------------------------------------------------------

    string[0] = 1;

    string[4] = 5;

    string.append("aaaaa");

//  ------------------------------------------------------------

    std::stringstream stream_1(string);

    std::stringstream stream_2;

//  ------------------------------------------------------------

    Entity entity;
	
//  ------------------------------------------------------------

    stream_1 >> entity;

    stream_2 << entity;

//  ------------------------------------------------------------

    assert(stream_2.str() == stream_1.str());
}