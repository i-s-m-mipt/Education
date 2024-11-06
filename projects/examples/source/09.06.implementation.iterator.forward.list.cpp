#include <iterator>
#include <memory>

//  ================================================================================================

template < typename T > class List
{
private:

	struct Node 
	{ 
		T value = T(); std::shared_ptr < Node > next; 
	};

public:

	class Iterator
	{
	public:

		using iterator_category = std::forward_iterator_tag;

//      --------------------------------------------------------------------------------------------

		explicit Iterator(std::shared_ptr < Node > node = nullptr) : m_node(node) {}

//      --------------------------------------------------------------------------------------------

		const auto operator++(int) 
		{ 
			auto copy(*this); 
			
			m_node = m_node->next; 
			
			return copy; 
		}

		auto & operator++() 
		{ 
			m_node = m_node->next; 
			
			return *this;
		}

		auto & operator*() const
		{ 
			return m_node->value; 
		}

		auto operator->() const
		{ 
			return &(m_node->value); 
		}

		auto operator==(const Iterator & other) const
		{ 
			return m_node == other.m_node; 
		}

	private:

		std::shared_ptr < Node > m_node;
	}; 

//  ------------------------------------------------------------------------------------------------

	auto begin() const { return Iterator(m_head); }
	auto end  () const { return Iterator(      ); }

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