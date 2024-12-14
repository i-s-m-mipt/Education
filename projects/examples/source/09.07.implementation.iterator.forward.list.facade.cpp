#include <iterator>
#include <memory>

#include <boost/iterator/iterator_facade.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////

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

	//  ----------------------------------------------------------------------------------------

		void increment() 
		{ 
			m_node = m_node->next; 
		}

		auto & dereference() const
		{ 
			return m_node->value; 
		}

		auto equal(const Iterator & other) const
		{ 
			return m_node == other.m_node; 
		};

	private:

		friend boost::iterator_core_access;

	//  ----------------------------------------------------------------------------------------

		std::shared_ptr < Node > m_node;
	};

//  --------------------------------------------------------------------------------------------
	
	auto begin() const { return Iterator(m_head); }
	auto end  () const { return Iterator(      ); }

//  --------------------------------------------------------------------------------------------

	void push_back(T value)
	{
		if (auto node = std::make_shared < Node > (value, nullptr); !m_head)
		{
			m_head = node;
		}
		else
		{
			auto last = m_head; for (; last->next; last = last->next); last->next = node;
		}
	}

private:

	std::shared_ptr < Node > m_head;
};

////////////////////////////////////////////////////////////////////////////////////////////////

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