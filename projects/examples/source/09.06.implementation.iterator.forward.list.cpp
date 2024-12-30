#include <iterator>
#include <memory>

/////////////////////////////////////////////////////////////////////////////////////////

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

//      ---------------------------------------------------------------------------------

		Iterator(std::shared_ptr < Node > node = nullptr) : m_node(node) {}

//      ---------------------------------------------------------------------------------

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
			return &m_node->value; 
		}

		auto operator==(const Iterator & other) const
		{ 
			return m_node == other.m_node; 
		}

	private:

		std::shared_ptr < Node > m_node;
	}; 

//  -------------------------------------------------------------------------------------

	auto begin() const { return Iterator(m_head); }
	auto end  () const { return Iterator(      ); }

//  -------------------------------------------------------------------------------------

	void push_back(T value)
	{
		auto node = std::make_shared < Node > (value, nullptr);

		if (m_head)
		{
			auto last = m_head; for (; last->next; last = last->next); last->next = node;
		}
		else
		{
			m_head = node;
		}
	}

private:

	std::shared_ptr < Node > m_head;
};

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	List < int > list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	for (auto iterator = std::begin(list); iterator != std::end(list); ++iterator);

	for ([[maybe_unused]] auto element : list);
}