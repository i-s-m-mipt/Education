///////////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////////////////////////////////////////////

// section : Iterator Classification

///////////////////////////////////////////////////////////////////////////////////

// content : List Iterators
//
// content : Operator ->
//
// content : Range-Based Statement for

///////////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <memory>

///////////////////////////////////////////////////////////////////////////////////

template < typename T > class List
{
private :

	struct Node
	{ 
		T x = T();

		std::shared_ptr < Node > next;
	};
	
public :

	class Iterator
	{
	public :

		using iterator_category = std::forward_iterator_tag;

	//  -------------------------------------------------------------------

		Iterator(std::shared_ptr < Node > node = nullptr) : m_node(node) {}

	//  -------------------------------------------------------------------

		auto const operator++(int)
		{
			auto x = *this;

			m_node = m_node->next;

			return x;
		}

	//  -------------------------------------------------------------------

		auto & operator++()
		{
			m_node = m_node->next;

			return *this;
		}

	//  -------------------------------------------------------------------

		auto & operator* () const { return  m_node->x; }

		auto   operator->() const { return &m_node->x; }

	//  -------------------------------------------------------------------

		friend auto operator==(Iterator const & lhs, Iterator const & rhs)
		{
			return lhs.m_node == rhs.m_node;
		}

	private :

		std::shared_ptr < Node > m_node;
	};

//  -----------------------------------------------------------------------

	auto begin() const { return Iterator(m_head); }

	auto end  () const { return Iterator(      ); }

//  -----------------------------------------------------------------------

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

private :

	std::shared_ptr < Node > m_head;
};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	List < int > list;

//  -------------------------------------------------------------------------------

	list.push_back(1);

//  -------------------------------------------------------------------------------

	for (auto iterator = std::begin(list); iterator != std::end(list); ++iterator);

//  -------------------------------------------------------------------------------

	for ([[maybe_unused]] auto element : list);
}

///////////////////////////////////////////////////////////////////////////////////