#include <bit>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

class Pool_Allocator
{
private:

	struct Block { Block * next = nullptr; };
	
public:

	explicit Pool_Allocator(std::size_t size, std::size_t size_block) : m_size(size)
	{
		m_size_block = std::max(size_block, sizeof(Block));
		
		m_size += (size % m_size_block);
		
		make_head(); m_begin = m_head;
	}

	~Pool_Allocator() noexcept
	{
		for (std::size_t i = 0; i < std::size(m_chains); ++i)
		{
			::operator delete(m_chains[i]);
		}
	}

	[[nodiscard]] void * allocate()
	{
		if (m_head == nullptr)
		{
			if (m_offset == std::size(m_chains))
			{
				make_head();
			}
			else m_head = extract_block(m_chains[++m_offset - 1]);
		}

		auto block = m_head;

		if (!block->next)
		{
			if (auto next  = std::bit_cast < std::byte * > (  block               ) + m_size_block;
				     next != std::bit_cast < std::byte * > (m_chains[m_offset - 1]) + m_size)
			{
				m_head = extract_block(next); m_head->next = nullptr;
			}
			else m_head = m_head->next;
		}
		else m_head = m_head->next;

		return block;
	}

	void deallocate(void * ptr) noexcept
	{
		auto block = extract_block(ptr); block->next = m_head; m_head = block;
	}

	void clear() noexcept // note: manual operation
	{
		for (std::size_t i = 0; i < std::size(m_chains); ++i)
		{
			extract_block(m_chains[i])->next = nullptr;
		}

		m_head = extract_block(m_begin); m_offset = 1;
	}

	void print() const
	{
		std::cout << m_head << std::endl;
	}

private:

	Block * extract_block(void * ptr) const 
	{ 
		return std::bit_cast < Block * > (ptr); 
	}

	Block * allocate_blocks() const
	{
		auto block = extract_block(::operator new(m_size)); 
		
		block->next = nullptr; return block;
	}

	void make_head()
	{
		m_head = allocate_blocks(); ++m_offset; m_chains.push_back(m_head);
	}

private:

	std::size_t m_size       = 0;
	std::size_t m_size_block = 0;
		
	Block * m_head = nullptr;

	std::size_t m_offset = 0;

	std::vector < void * > m_chains;

	void * m_begin = nullptr;

}; // class Pool_Allocator

int main()
{
	Pool_Allocator allocator(32, 8); allocator.print(); // note: initial

	[[maybe_unused]] auto ptr_0 = allocator.allocate(); allocator.print(); // note: head X
	[[maybe_unused]] auto ptr_1 = allocator.allocate(); allocator.print(); // note: head Y
	[[maybe_unused]] auto ptr_2 = allocator.allocate(); allocator.print();
	[[maybe_unused]] auto ptr_3 = allocator.allocate(); allocator.print(); // note: nullptr

	[[maybe_unused]] auto ptr_4 = allocator.allocate(); allocator.print(); // note: head Z

	allocator.deallocate(ptr_1); allocator.print(); // note: head X
	allocator.deallocate(ptr_2); allocator.print(); // note: head Y

	[[maybe_unused]] auto ptr_5 = allocator.allocate(); allocator.print(); // note: head X
	[[maybe_unused]] auto ptr_6 = allocator.allocate(); allocator.print(); // note: head Z

	allocator.clear(); allocator.print(); // note: same as initial

	[[maybe_unused]] auto ptr_7 = allocator.allocate(); allocator.print(); // note: head X

	return 0;
}