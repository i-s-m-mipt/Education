#include <cassert>
#include <forward_list>
#include <iterator>
#include <type_traits>

////////////////////////////////////////////////////////////////////

int main()
{
    std::forward_list < int > list = { 1, 2, 3, 4, 5 };

//  ----------------------------------------------------------------

//  auto size = std::size(list); // error

    auto size = 1uz;

//  ----------------------------------------------------------------

    auto iterator = std::begin(list);

//  ----------------------------------------------------------------

    while (std::next(iterator) != std::end(list))
    {
        ++size;

        ++iterator;
    }

//  ----------------------------------------------------------------

    list.insert_after(iterator, 1);

    list. erase_after(iterator);

//  ----------------------------------------------------------------
		
	list.push_front(1);

    list. pop_front( );

//  ----------------------------------------------------------------

	list.insert_after(std::next(std::begin(list), size / 2), 1);

	list. erase_after(std::next(std::begin(list), size / 2));

//  ----------------------------------------------------------------

    static_assert
    (
        std::is_same_v 
        < 
            std::forward_list < int > ::iterator::iterator_category,
            
            std::forward_iterator_tag 
        > 
    );
}