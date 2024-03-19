#include <iostream>
#include <iterator>
#include <memory>

#include <boost/iterator/iterator_facade.hpp>

template < typename T > class List
{
private:

	struct Node { T value{}; std::shared_ptr < Node > next; };

public:

	class Iterator : public boost::iterator_facade < Iterator, T, boost::forward_traversal_tag > // note: CRTP
	{
	public:

		explicit Iterator(std::shared_ptr < Node > node = nullptr) noexcept : m_node(node) {}

		friend class boost::iterator_core_access;

	public:

		void increment() noexcept { m_node = m_node->next; }

		[[nodiscard]] T & dereference() const noexcept { return m_node->value; }

		[[nodiscard]] bool equal(const Iterator & other) const noexcept
		{ 
			return (m_node == other.m_node); 
		};

	private:

		std::shared_ptr < Node > m_node;

	}; // class Iterator

public:

	[[nodiscard]] constexpr Iterator begin() noexcept { return Iterator(m_head); }
	[[nodiscard]] constexpr Iterator end  () noexcept { return Iterator(      ); }

	void push_back(T value)
	{
		if (auto new_node = std::make_shared < Node > (value, nullptr); !m_head)
		{
			m_head = new_node;
		}
		else
		{
			auto p = m_head; for (; p->next; p = p->next); p->next = new_node;
		}
	}

private:

	std::shared_ptr < Node > m_head;

}; // template < typename T > class List

int main()
{
	List < int > list;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	for (auto iterator = std::begin(list); iterator != std::end(list); ++iterator)
	{
		std::cout << *iterator << ' ';
	}

	std::cout << std::endl;

	for (const auto element : list) std::cout << element << ' ';

	std::cout << std::endl;

	return 0;
}