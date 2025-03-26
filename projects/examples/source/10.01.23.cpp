#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <boost/flyweight.hpp>

//////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x, const std::string & string) 
    : 
        m_flyweight_1(x), 
        
        m_flyweight_2(string) 
    {}

//  ----------------------------------------------------------------------

    const auto & flyweight_1() const { return m_flyweight_1; }

    const auto & flyweight_2() const { return m_flyweight_2; }

private :

    using alias_1 = int;

    using alias_2 = std::string;

//  ----------------------------------------------------------------------

    template < typename T > using tag_t = boost::flyweights::tag < T > ;

//  ----------------------------------------------------------------------

    struct flyweight_1_tag {};

    struct flyweight_2_tag {};

//  ----------------------------------------------------------------------

    boost::flyweight < alias_1, tag_t < flyweight_1_tag > > m_flyweight_1;

    boost::flyweight < alias_2, tag_t < flyweight_2_tag > > m_flyweight_2;
};

//////////////////////////////////////////////////////////////////////////

int main() 
{
    auto size_1 = 1'000'000uz, size_2 = 1'000uz;

    std::vector < Entity > entities;

    for (auto i = 0uz; i < size_1; ++i)
    {
        entities.emplace_back(1, std::string(size_2, 'a'));
    }

//  ----------------------------------------------------------------------------

    std::cout << "main : enter char : "; std::cin.get();

//  ----------------------------------------------------------------------------

    auto & entity = entities.front();

//  ----------------------------------------------------------------------------

    for (auto i = 1uz; i < size_1; ++i)
    {
        assert(&entity.flyweight_1().get() == &entities[i].flyweight_1().get());

        assert(&entity.flyweight_2().get() == &entities[i].flyweight_2().get());
    }

//  ----------------------------------------------------------------------------

    entity = Entity(2, std::string(size_2, 'b'));

//  ----------------------------------------------------------------------------

    for (auto i = 1uz; i < size_1; ++i)
    {
        assert(&entity.flyweight_1().get() != &entities[i].flyweight_1().get());

        assert(&entity.flyweight_2().get() != &entities[i].flyweight_2().get());
    }
}