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

/////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Visitor
{
public:

    void operator()(const std::any & any) const
    {
        std::cout << "Visitor::operator() : any = " << std::any_cast < T > (any) << '\n';
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    using data_1_t = int;

    using data_2_t = std::string;

//  -----------------------------------------------------------------------------------------

    std::unordered_map < std::type_index, std::function < void(const std::any &) > > visitors
    {
        std::make_pair(std::type_index(typeid(data_1_t)), Visitor < data_1_t > ()),
        std::make_pair(std::type_index(typeid(data_2_t)), Visitor < data_2_t > ())
    };

//  -----------------------------------------------------------------------------------------

    for (const auto & element : std::vector < std::any > { 1, "aaaaa"s }) 
    {
        auto iterator = visitors.find(std::type_index(element.type()));

        if (iterator != std::end(visitors))
        {
            iterator->second(element);
        }
    }
}