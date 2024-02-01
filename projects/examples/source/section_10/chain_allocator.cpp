#include <bit>
#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

class Chain_Allocator // note: used with deallocations at any position for blocks of fixed sizes
{
private:

	struct Block { Block * next = nullptr; };
	
public:

	explicit Chain_Allocator(std::size_t size, std::size_t size_block) : m_size(size)
	{
		m_size_block = std::max(size_block, sizeof(Block));

		if (m_size % m_size_block != 0)
		{
			throw std::runtime_error("invalid size");
		}

		make_chain(); m_begin = m_head;
	}

	~Chain_Allocator() noexcept
	{
		for (std::size_t i = 0; i < std::size(m_chains); ++i)
		{
			::operator delete(m_chains[i], default_alignment);
		}
	}

	[[nodiscard]] void * allocate()
	{
		if (m_head == nullptr) // note: current chain has ended
		{
			if (m_offset == std::size(m_chains))
			{
				make_chain();
			}
			else m_head = get_block(m_chains[++m_offset - 1]); // note: switch to next chain
		}

		auto block = m_head;

		if (!block->next) // note: try switch to next block in current chain
		{
			if (auto next  = get_byte(  block               ) + m_size_block; 
				     next != get_byte(m_chains[m_offset - 1]) + m_size)
			{
				m_head = get_block(next); m_head->next = nullptr;
			}
			else m_head = m_head->next; // note: current chain has ended
		}
		else m_head = m_head->next; // note: next after deallocation

		return block;
	}

	void deallocate(void * ptr) noexcept
	{
		auto block = get_block(ptr); 
		
		block->next = m_head; m_head = block; // note: link freed block to previous head
	}

	void print() const
	{
		std::cout << m_head << std::endl;
	}

private:

	std::byte * get_byte(void * ptr) const noexcept
	{
		return std::bit_cast < std::byte * > (ptr);
	}

	Block * get_block(void * ptr) const noexcept
	{ 
		return std::bit_cast < Block * > (ptr); 
	}

	Block * allocate_blocks() const
	{
		auto block = get_block(::operator new(m_size, default_alignment));
		
		block->next = nullptr; return block;
	}

	void make_chain()
	{
		m_head = allocate_blocks(); ++m_offset; m_chains.push_back(m_head);
	}

public:

	static inline const std::align_val_t default_alignment { alignof(std::max_align_t) };

private:

	std::size_t m_size       = 0;
	std::size_t m_size_block = 0;
		
	Block * m_head = nullptr;

	std::size_t m_offset = 0;

	std::vector < void * > m_chains;

	void * m_begin = nullptr;

}; // class Chain_Allocator

int main(int argc, char ** argv) // note: arguments for benchmark
{
	Chain_Allocator allocator(32, 8);                   allocator.print(); // note: initial

	[[maybe_unused]] auto ptr_0 = allocator.allocate(); allocator.print(); // note: head X
	[[maybe_unused]] auto ptr_1 = allocator.allocate(); allocator.print(); // note: head Y
	[[maybe_unused]] auto ptr_2 = allocator.allocate(); allocator.print();
	[[maybe_unused]] auto ptr_3 = allocator.allocate(); allocator.print(); // note: nullptr

	[[maybe_unused]] auto ptr_4 = allocator.allocate(); allocator.print(); // note: head Z

	allocator.deallocate(ptr_1);                        allocator.print(); // note: head X
	allocator.deallocate(ptr_2);                        allocator.print(); // note: head Y

	[[maybe_unused]] auto ptr_5 = allocator.allocate(); allocator.print(); // note: head X
	[[maybe_unused]] auto ptr_6 = allocator.allocate(); allocator.print(); // note: head Z

	return 0;
}