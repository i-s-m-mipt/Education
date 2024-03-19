#include <iostream>
#include <iterator>
#include <memory>

template < typename T > class List
{
private:

	struct Node // note: can be implemented as separate struct template
	{ 
		T value{}; std::shared_ptr < Node > next; // note: no allocators
	};

public:

	class Iterator // note: can be implemented as separate class template
	{
	public:

		using iterator_category = std::forward_iterator_tag; // note: forward iterator

		explicit Iterator(std::shared_ptr < Node > node = nullptr) noexcept : m_node(node) {}

	public:

		Iterator & operator++() noexcept 
		{ 
			m_node = m_node->next; return *this; // note: undefined behaviour if end
		}

		Iterator operator++(int) noexcept 
		{ 
			auto prev = *this; ++(*this); return prev; 
		}

		[[nodiscard]] T & operator* () const noexcept { return  (m_node->value); }
		[[nodiscard]] T * operator->() const noexcept { return &(m_node->value); }

		[[nodiscard]] bool operator==(const Iterator & other) const noexcept 
		{ 
			return (m_node == other.m_node); 
		}

	private:

		std::shared_ptr < Node > m_node; // note: no allocators

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

	std::shared_ptr < Node > m_head; // note: no allocators

}; // template < typename T > class List

class C { public: void f() const { std::cout << "C::f" << std::endl; } };

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

	List < C > c_list;

	c_list.push_back(C());

	std::begin(c_list)->f(); // note: iterator.operator->()->f()

	return 0;
}