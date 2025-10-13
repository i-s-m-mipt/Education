///////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <forward_list>
#include <iterator>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////

template < typename L, typename I > void erase(L & list, I iterator)
{
    auto previous = list.before_begin();

    while (std::next(previous) != iterator)
    {
        ++previous;
    }

    list.erase_after(previous);
}

///////////////////////////////////////////////////////////////////////////

int main()
{
    std::forward_list < int > list = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------------------

    static_assert
    (
        std::is_same_v 
        < 
            decltype(list)::iterator::iterator_category,
            
            std::forward_iterator_tag 
        > 
    );

//  -----------------------------------------------------------------------

//  assert(std::size(list) == 5); // error

//  -----------------------------------------------------------------------

    ::erase(list, list.insert_after(std::next(list.before_begin(), 0), 1));

	::erase(list, list.insert_after(std::next(list.before_begin(), 2), 1));

	::erase(list, list.insert_after(std::next(list.before_begin(), 5), 1));

//  -----------------------------------------------------------------------

//  assert(list.at(0) == 1); // error
}

///////////////////////////////////////////////////////////////////////////