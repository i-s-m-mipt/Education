#include <any>
#include <functional>
#include <iostream>
#include <iterator>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

//  ================================================================================================

template < typename T, typename F > auto make_visitor(F && f)
{
    return std::make_pair
    (
        std::type_index(typeid(T)), [f](const auto & any)
        { 
            f(std::any_cast < T > (any)); 
        }
    );
}

//  ================================================================================================

void visit(const std::any & any)
{
    static auto visitor = [](auto x){ std::cout << x << '\n'; };

    static std::unordered_map < std::type_index, std::function < void(const std::any &) > > visitors
    {
        make_visitor < char   > (visitor),
        make_visitor < int    > (visitor),
        make_visitor < double > (visitor)
    };

    if (auto iterator = visitors.find(std::type_index(any.type())); iterator != std::cend(visitors))
    {
        iterator->second(any);
    }
}

//  ================================================================================================

int main()
{
    std::vector < std::any > vector { 'a', 1, 1.0, "aaaaa" };

    for (const auto & element : vector) 
    {
        visit(element);
    }
}