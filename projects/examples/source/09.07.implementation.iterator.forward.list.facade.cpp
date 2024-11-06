#include <iostream>
#include <iterator>
#include <memory>

#include <boost/iterator/iterator_facade.hpp>

//  ================================================================================================

template < typename T > class List
{
private:

	struct Node 
	{ 
		T value = T(); std::shared_ptr < Node > next; 
	};

public:

	class Iterator : public boost::iterator_facade < Iterator, T, boost::forward_traversal_tag >
	{
	public:

		explicit Iterator(std::shared_ptr < Node > node = nullptr) : m_node(node) {}

//      --------------------------------------------------------------------------------------------

		friend boost::iterator_core_access;

//      --------------------------------------------------------------------------------------------

		void increment() 
		{ 
			m_node = m_node->next; 
		}

		[[nodiscard]] auto & dereference() const
		{ 
			return m_node->value; 
		}

		[[nodiscard]] auto equal(const Iterator & other) const
		{ 
			return m_node == other.m_node; 
		};

	private:

		std::shared_ptr < Node > m_node;
	};

//  ------------------------------------------------------------------------------------------------

	[[nodiscard]] auto begin() const { return Iterator(m_head); }
	[[nodiscard]] auto end  () const { return Iterator(      ); }

//  ------------------------------------------------------------------------------------------------

	void push_back(T value)
	{
		if (auto new_node = std::make_shared < Node > (value, nullptr); !m_head)
		{
			m_head = new_node;
		}
		else
		{
			auto node = m_head; for (; node->next; node = node->next); node->next = new_node;
		}
	}

private:

	std::shared_ptr < Node > m_head;
};

//  ================================================================================================

int main()
{
	List < int > list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	for (auto iterator = std::cbegin(list); iterator != std::cend(list); ++iterator);

	for ([[maybe_unused]] auto element : list);
}