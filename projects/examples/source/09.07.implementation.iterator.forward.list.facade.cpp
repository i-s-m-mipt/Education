#include <iterator>
#include <memory>

#include <boost/iterator/iterator_facade.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class List
{
private:

	struct Node 
	{ 
		T data = T(); std::shared_ptr < Node > next; 
	};

public:

	class Iterator : public boost::iterator_facade < Iterator, T, boost::forward_traversal_tag >
	{
	public:

		Iterator(std::shared_ptr < Node > node = nullptr) : m_node(node) {}

	//  ----------------------------------------------------------------------------------------

		void increment() 
		{ 
			m_node = m_node->next; 
		}

		auto & dereference() const
		{ 
			return m_node->data; 
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

	void push_back(T x)
	{
		auto node = std::make_shared < Node > (x, nullptr);

		if (m_head)
		{
			auto tail = m_head; 
			
			while (tail->next) 
			{
				tail = tail->next;
			} 
			
			tail->next = node;
		}
		else
		{
			m_head = node;
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

	for (auto iterator = std::begin(list); iterator != std::end(list); ++iterator);

	for ([[maybe_unused]] auto element : list);
}