#include <any>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Visitor
{
public :

    void operator()(const std::any & any) const
    {
        std::cout << "Visitor::operator() : any = " << std::any_cast < T > (any) << '\n';
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using alias_1 = int;

    using alias_2 = std::string;

//  -------------------------------------------------------------------------------------------

    std::unordered_map < std::type_index, std::function < void(const std::any &) > > visitors =
    {
        std::make_pair(std::type_index(typeid(alias_1)), Visitor < alias_1 > ()),
        
        std::make_pair(std::type_index(typeid(alias_2)), Visitor < alias_2 > ())
    };

//  -------------------------------------------------------------------------------------------

    for (const auto & any : std::vector < std::any > ({ 1, "aaaaa"s })) 
    {
        std::type_index type_index(any.type());

        if (auto iterator = visitors.find(type_index); iterator != std::end(visitors))
        {
            iterator->second(any);
        }
    }
}