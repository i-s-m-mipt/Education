#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

//////////////////////////////////////////////////////////////////

template <typename... Ts> 
class Tuple 
{
public:
    static constexpr std::size_t Size() 
    {
        return sizeof...(Ts);
    }
};

//////////////////////////////////////////////////////////////////

template <typename T, typename... Ts> 
class Tuple<T, Ts...>
{
public:
    Tuple(T&& x, Ts&&... ys)
        : m_head(std::forward<T>(x)),
          m_tail(std::forward<Ts>(ys)...)
    {}

    static constexpr std::size_t Size() 
    {
        return sizeof...(Ts) + 1;
    }

    // ------------------------------------------------

    template <std::size_t I> 
    auto get() const
    {
        if constexpr (I > 0)
        {
            return m_tail.template get<I - 1>();
        }
        else
        {
            return m_head;
        }
    }

private:
    T m_head;
    Tuple<Ts...> m_tail;
};

//////////////////////////////////////////////////////////////////

static_assert(Tuple<>::Size() == 0, "Empty tuple size should be 0");
static_assert(Tuple<int>::Size() == 1, "Single element tuple size should be 1");
static_assert(Tuple<int, double>::Size() == 2, "Two elements tuple size should be 2");
static_assert(Tuple<int, double, std::string>::Size() == 3, "Three elements tuple size should be 3");
static_assert(Tuple<int, double, std::string, char>::Size() == 4, "Four elements tuple size should be 4");

//////////////////////////////////////////////////////////////////

int main()
{
    Tuple<int, double, std::string> tuple(1, 2.0, "aaaaa");

    assert(tuple.get<0>() == 1);
    assert(tuple.get<1>() == 2.0);
    assert(tuple.get<2>() == "aaaaa");

    assert(tuple.Size() == 3);

    constexpr std::size_t size1 = Tuple<int>::Size();
    static_assert(size1 == 1, "Size should be 1");

    constexpr std::size_t size2 = Tuple<int, double>::Size();
    static_assert(size2 == 2, "Size should be 2");

    constexpr std::size_t size3 = Tuple<int, double, std::string>::Size();
    static_assert(size3 == 3, "Size should be 3");

    return 0;
}