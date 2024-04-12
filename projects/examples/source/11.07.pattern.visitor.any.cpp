#include <any>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

template < typename T, typename F > [[nodiscard]] inline auto make_visitor(F f)
{
    return std::make_pair(std::type_index(typeid(T)), [f](const auto & any)
    { 
        f(std::any_cast < T > (any)); 
    });
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

    if (auto iterator = visitors.find(std::type_index(any.type())); iterator != std::cend(visitors))
    {
        iterator->second(any);
    }
    else throw std::invalid_argument("invalid type: " + std::string(any.type().name()));
}

int main()
{
    const std::vector < std::any > vector = { true, 'a', 42, 3.14, "hello" };

    try
    {
        for (const auto & element : vector) handle(element);
    }
    catch (const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }

    return 0;
}