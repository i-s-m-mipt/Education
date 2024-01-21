#include <any>
#include <functional>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

template < typename T, typename F > auto inline make_visitor(F f)
{
    return std::make_pair(std::type_index(typeid(T)), [f](const auto & any){ f(std::any_cast < T > (any)); });
}

void handle(const std::any & any)
{
    using type_b = bool;
    using type_c = char;
    using type_i = int;
    using type_d = double;

    static std::unordered_map < std::type_index, std::function < void(const std::any &) > > visitors
    {
        make_visitor < type_b > ([](type_b x){ std::cout << x << std::endl; }),
        make_visitor < type_c > ([](type_c x){ std::cout << x << std::endl; }),
        make_visitor < type_i > ([](type_i x){ std::cout << x << std::endl; }),
        make_visitor < type_d > ([](type_d x){ std::cout << x << std::endl; })
    };

    if (const auto iterator = visitors.find(std::type_index(any.type())); iterator != std::cend(visitors))
    {
        iterator->second(any);
    }
    else
    {
        throw std::runtime_error("invalid type " + std::string(any.type().name()));
    }
}

int main()
{
    std::vector < std::any > vector = { true, 'a', 42, 3.14 };

    for (std::size_t i = 0; i < std::size(vector); ++i)
    {
        handle(vector[i]);
    }
}