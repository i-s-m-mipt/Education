#include <bit>
#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/noncopyable.hpp>

#include <benchmark/benchmark.h>

//  ================================================================================================

class Chain_Allocator : private boost::noncopyable
{
private:

	struct Node { Node * next = nullptr; };
	
public:

	explicit Chain_Allocator(std::size_t size, std::size_t size_node) : m_size(size), m_size_node(size_node)
	{
		if (m_size % m_size_node == 0 && m_size_node >= sizeof(Node))
		{
			make_chain(); m_begin = m_head;
		}
		else throw std::runtime_error("invalid size");
	}

   ~Chain_Allocator() noexcept
	{
		for (const auto chain : m_chains) ::operator delete(chain, m_size, default_alignment);
	}

public:

	[[nodiscard]] void * allocate()
	{
		if (m_head == nullptr)
		{
			if (m_offset == std::size(m_chains))
			{
				make_chain();
			}
			else m_head = get_node(m_chains[++m_offset - 1]);
		}

		const auto node = m_head;

		if (!node->next)
		{
			if (const auto next  = get_byte(   node               ) + m_size_node; 
				           next != get_byte(m_chains[m_offset - 1]) + m_size)
			{
				m_head = get_node(next); m_head->next = nullptr;
			}
			else m_head = m_head->next;
		}
		else m_head = m_head->next;

		return node;
	}

	void deallocate(void * ptr) noexcept
	{
		const auto node = get_node(ptr); 
		
		node->next = m_head; m_head = node;
	}

	void print() const 
	{ 
		std::cout << std::bit_cast < std::size_t > (m_head) << std::endl; 
	}

private:

	[[nodiscard]] std::byte * get_byte(void * ptr) const noexcept
	{
		return static_cast < std::byte * > (ptr);
	}

	[[nodiscard]] Node * get_node(void * ptr) const noexcept
	{ 
		return static_cast < Node * > (ptr); 
	}

	[[nodiscard]] Node * allocate_nodes() const
	{
		const auto node = get_node(::operator new(m_size, default_alignment));
		
		node->next = nullptr; 
		
		return node;
	}

	void make_chain()
	{
		m_head = allocate_nodes(); ++m_offset; m_chains.push_back(m_head);
	}

public:

	static constexpr std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

	const std::size_t m_size      = 0;
	const std::size_t m_size_node = 0;

private:

	std::size_t m_offset = 0;

	void * m_begin = nullptr;
	Node * m_head  = nullptr;

	std::vector < void * > m_chains;

}; // class Chain_Allocator : private boost::noncopyable

//  ================================================================================================

void test_1(benchmark::State & state)
{
	constexpr std::size_t kb = 1024, mb = kb * kb, gb = kb * kb * kb;

	std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		Chain_Allocator allocator(gb, mb);

		for (std::size_t i = 0; i < kb; i += 1) pointers[i] = allocator.  allocate(           );
		for (std::size_t i = 0; i < kb; i += 2)               allocator.deallocate(pointers[i]);
		for (std::size_t i = 0; i < kb; i += 2) pointers[i] = allocator.  allocate(           );
		for (std::size_t i = 0; i < kb; i += 1)               allocator.deallocate(pointers[i]);
	}
}

//  ================================================================================================

void test_2(benchmark::State & state)
{
	constexpr std::size_t kb = 1024, mb = kb * kb;

	std::vector < void * > pointers(kb, nullptr);

	for (auto _ : state)
	{
		for (std::size_t i = 0; i < kb; i += 1) pointers[i] = ::operator    new(             mb);
		for (std::size_t i = 0; i < kb; i += 2)               ::operator delete(pointers[i], mb);
		for (std::size_t i = 0; i < kb; i += 2) pointers[i] = ::operator    new(             mb);
		for (std::size_t i = 0; i < kb; i += 1)               ::operator delete(pointers[i], mb);
	}
}

//  ================================================================================================

BENCHMARK(test_1);
BENCHMARK(test_2);

//  ================================================================================================

int main(int argc, char ** argv)
{
	Chain_Allocator allocator(32, 8);                          allocator.print(); // detail: X

	[[maybe_unused]] auto ptr_A = allocator.  allocate(     ); allocator.print(); // detail: X + 8
	[[maybe_unused]] auto ptr_B = allocator.  allocate(     ); allocator.print(); // detail: X + 8 + 8
	[[maybe_unused]] auto ptr_C = allocator.  allocate(     ); allocator.print(); // detail: X + 8 + 8 + 8
	[[maybe_unused]] auto ptr_D = allocator.  allocate(     ); allocator.print(); // detail: 0

	[[maybe_unused]] auto ptr_E = allocator.  allocate(     ); allocator.print(); // detail: Y

	                              allocator.deallocate(ptr_B); allocator.print(); // detail: X + 8
	                              allocator.deallocate(ptr_C); allocator.print(); // detail: X + 8 + 8

	[[maybe_unused]] auto ptr_F = allocator.  allocate(     ); allocator.print(); // detail: X + 8
	[[maybe_unused]] auto ptr_G = allocator.  allocate(     ); allocator.print(); // detail: Y

//  ================================================================================================

	benchmark::Initialize(&argc, argv);

	benchmark::RunSpecifiedBenchmarks();

	return 0;
}