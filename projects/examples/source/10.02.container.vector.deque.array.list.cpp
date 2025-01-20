#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data = 0; 
};

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto size = 5uz;

		std::vector < int > vector;
		
		vector.resize(2 * size); assert(vector.size() == size * 2 && vector.capacity() == size * 2);
		vector.resize    (size); assert(vector.size() == size     && vector.capacity() == size * 2);
		vector.shrink_to_fit (); assert(vector.size() == size     && vector.capacity() == size    );
		vector.clear         (); assert(vector.size() == 0        && vector.capacity() == size    );
		vector.shrink_to_fit (); assert(vector.size() == 0        && vector.capacity() == 0       );
		vector.reserve   (size); assert(vector.size() == 0        && vector.capacity() == size    );
		vector.resize    (size); assert(vector.size() == size     && vector.capacity() == size    );
		vector.push_back    (1); assert(vector.size() == size + 1 && vector.capacity() >= size + 1);
		vector.shrink_to_fit (); assert(vector.size() == size + 1 && vector.capacity() == size + 1);
		vector.pop_back      (); assert(vector.size() == size     && vector.capacity() == size + 1);
		vector.shrink_to_fit (); assert(vector.size() == size     && vector.capacity() == size    );
	}
	
//  ------------------------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		try
		{
			vector.at(1'000) = 1;
		}
		catch (const std::out_of_range & exception) 
		{
			std::cerr << "main : " << exception.what() << '\n';
		}

		for (auto i = 0uz; i < std::size(vector); ++i)
		{		
			assert(vector[i] == i + 1);
		}
	}

//  ------------------------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

//		for (auto i = std:: size(vector) - 1; i >= 0; --i); // error

		for (auto i = std::ssize(vector) - 1; i >= 0; --i);
	}

//  ------------------------------------------------------------------------------------------------

	{
		int array[5]{ 1, 2, 3, 4, 5 };

//		assert(array.size() == 5); // error

		assert(std::size(array) == 5 && *std::begin(array) == 1);
	}
	
//  ------------------------------------------------------------------------------------------------

	{
		std::vector < Entity > entities_1 = { { 1 }, { 2 }, { 3 }, { 4 }, { 5 } };

		std::vector < Entity > entities_2(std::begin(entities_1), std::end(entities_1));

		auto begin = std::make_move_iterator(std::begin(entities_2));

		auto end   = std::make_move_iterator(std::end  (entities_2));

		std::vector < Entity > entities_3(begin, end);

		entities_3.insert
		(
			std::end(entities_3), std::begin(entities_1), std::next(std::begin(entities_1))
		);

		assert(std::size(entities_3) == 6);

		entities_3.erase(std::begin(entities_3), std::prev(std::end(entities_3), 2));

		assert(std::size(entities_3) == 2);

		entities_3.insert (std::end(entities_3), Entity(1));

		entities_3.emplace(std::end(entities_3), 1);
	}

//  ------------------------------------------------------------------------------------------------
	
	{
		[[maybe_unused]] auto x { 1 };

//		[[maybe_unused]] auto initializer_list_1   { 1, 2, 3, 4, 5 }; // error

		[[maybe_unused]] auto initializer_list_2 = { 1, 2, 3, 4, 5 };
	}

//  ------------------------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		vector.push_back(1); 

		vector.insert(std::begin(vector), 1);

		vector.insert(std::next(std::begin(vector), std::size(vector) / 2), 1);

		vector.pop_back();

		vector.erase(std::begin(vector));

		vector.erase(std::next(std::begin(vector), std::size(vector) / 2));

		assert(vector[0] == 1);
	}

//  ------------------------------------------------------------------------------------------------

	{
		std::deque < int > deque = { 1, 2, 3, 4, 5 };

		deque.push_back(1); 
		
		deque.push_front(1); 

		deque.insert(std::next(std::begin(deque), std::size(deque) / 2), 1);

		deque.pop_back(); 
		
		deque.pop_front();

		deque.erase (std::next(std::begin(deque), std::size(deque) / 2));

		assert(deque[0] == 1);
	}

//  ------------------------------------------------------------------------------------------------

	{
		std::array < int, 5 > array_1 = { 1, 2, 3, 4, 5 };

		assert(array_1[0] == 1);

		int array_2[5]{ 1, 2, 3, 4, 5 };

		std::ignore = std::to_array(array_2);
	}

//  ------------------------------------------------------------------------------------------------

	{
		std::list < int > list_1 = { 5, 3, 1, 5, 3, 1 };

//		std::ranges::sort(list_1); // error
	
		list_1.sort();

		assert(list_1.unique() == 3);

		std::list < int > list_2 = { 4, 2, 0 };

		list_2.reverse();

		assert(list_2.remove(0) == 1);

		list_1.merge(list_2);

		list_2.splice(std::begin(list_2), list_1, std::begin(list_1), std::end(list_1));

		assert(list_2 == std::list < int > ({ 1, 2, 3, 4, 5 }));
	}

//  ------------------------------------------------------------------------------------------------

	{
		std::forward_list < int > forward_list = { 1, 2, 3, 4, 5 };

		forward_list.insert_after(forward_list.before_begin(), 1);

		forward_list.erase_after(std::begin(forward_list)); 

		assert(forward_list == std::forward_list < int > ({ 1, 2, 3, 4, 5 }));

//		assert(std::size(forward_list) == 5); // error
	}

//  ------------------------------------------------------------------------------------------------

	{
		std::list < int > list = { 5, 4, 3, 2, 1 };

//		std::ranges::sort(list); // error

		std::vector < std::reference_wrapper < int > > vector(std::begin(list), std::end(list));

		std::ranges::sort(vector);

		std::vector < int > result = { 1, 2, 3, 4, 5 };

		for (auto i = 0uz; i < std::size(vector); ++i)
		{
			assert(vector[i] == result[i]);
		}
	}
}