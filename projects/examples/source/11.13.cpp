///////////////////////////////////////////////////////////////////////////////////////////////

#include <any>
#include <functional>
#include <iterator>
#include <print>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Visitor
{
public :

    void operator()(std::any const & any) const
    {
        std::print("Visitor::operator() : any = {}\n", std::any_cast < T > (any));
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using alias_1 = int;

    using alias_2 = std::string;

//  -------------------------------------------------------------------------------------------

    std::unordered_map < std::type_index, std::function < void(std::any const &) > > visitors =
    {
        std::make_pair(std::type_index(typeid(alias_1)), Visitor < alias_1 > ()),
        
        std::make_pair(std::type_index(typeid(alias_2)), Visitor < alias_2 > ())
    };

//  -------------------------------------------------------------------------------------------

    for (auto const & any : std::vector < std::any > ({ 1, "aaaaa"s })) 
    {
        std::type_index type_index(any.type());

    //  ------------------------------------------------------------------------------

        if (auto iterator = visitors.find(type_index); iterator != std::end(visitors))
        {
            iterator->second(any);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////