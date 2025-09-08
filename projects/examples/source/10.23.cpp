////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

#include <boost/flyweight.hpp>

////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int x, std::string const & string) 
    : 
        m_flyweight_1(x), 
        
        m_flyweight_2(string) 
    {}

//  ----------------------------------------------------------------------

    auto const & flyweight_1() const { return m_flyweight_1; }

    auto const & flyweight_2() const { return m_flyweight_2; }

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

////////////////////////////////////////////////////////////////////////////////

int main() 
{
    std::vector < Entity > entities;

//  ----------------------------------------------------------------------------

    auto size = 1'000'000uz;

//  ----------------------------------------------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        entities.emplace_back(1, std::string(1'000, 'a'));
    }

//  ----------------------------------------------------------------------------

    std::cout << "main : enter char : "; std::cin.get();

//  ----------------------------------------------------------------------------

    auto & entity = entities.front();

//  ----------------------------------------------------------------------------

    for (auto i = 1uz; i < size; ++i)
    {
        assert(&entity.flyweight_1().get() == &entities[i].flyweight_1().get());

        assert(&entity.flyweight_2().get() == &entities[i].flyweight_2().get());
    }

//  ----------------------------------------------------------------------------

    entity = Entity(2, std::string(1'001, 'a'));

//  ----------------------------------------------------------------------------

    for (auto i = 1uz; i < size; ++i)
    {
        assert(&entity.flyweight_1().get() != &entities[i].flyweight_1().get());

        assert(&entity.flyweight_2().get() != &entities[i].flyweight_2().get());
    }
}

////////////////////////////////////////////////////////////////////////////////