#include <iostream>
#include <iterator>
#include <memory>

//  ================================================================================================

template < typename T > class List
{
private:

	struct Node { T value{}; std::shared_ptr < Node > next; };

public:

	class Iterator
	{
	public:

		using iterator_category = std::forward_iterator_tag;

		constexpr explicit Iterator(std::shared_ptr < Node > node = nullptr) noexcept : m_node(node) {}

	public:

		constexpr Iterator & operator++() noexcept 
		{ 
			m_node = m_node->next; return *this;
		}

		constexpr const Iterator operator++(int) noexcept 
		{ 
			auto prev = *this; ++(*this); return prev; 
		}

		[[nodiscard]] constexpr T & operator* () const noexcept { return  (m_node->value); }
		[[nodiscard]] constexpr T * operator->() const noexcept { return &(m_node->value); }

		[[nodiscard]] constexpr bool operator==(const Iterator & other) const noexcept 
		{ 
			return (m_node == other.m_node); 
		}

	private:

		std::shared_ptr < Node > m_node;

	}; // class Iterator

public:

	[[nodiscard]] constexpr Iterator begin() const noexcept { return Iterator(m_head); }
	[[nodiscard]] constexpr Iterator end  () const noexcept { return Iterator(      ); }

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

}; // template < typename T > class List

//  ================================================================================================

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