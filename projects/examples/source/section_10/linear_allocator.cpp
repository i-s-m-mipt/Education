#include <bit>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

class Linear_Allocator // note: used without partial deallocations for known total size
{
public:

	explicit Linear_Allocator(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size);
	}

	~Linear_Allocator() noexcept // note: final deallocation once
	{
		::operator delete(m_begin);
	}

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t))
	{
		void * first = std::bit_cast < std::byte * > (m_begin) + m_offset; // note: first free byte

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first) // note: modifies first and space
		{
			m_offset = m_size - space + size; 
			
			return first; // note: pointer aligned successfully
		}
		else return nullptr; // note: pointer not aligned
	}

	void print() const
	{
		std::cout << m_begin << ": " << std::setw(std::size(std::to_string(m_size))) << 
			std::right << std::setfill('0') << m_offset << " / " << m_size << std::endl;
	}

private:
	
	std::size_t m_size   = 0;
	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Linear_Allocator

int main()
{
	Linear_Allocator allocator(1024); 

	std::cout << allocator.allocate(  1, 4) << ' '; allocator.print(); // note: A
	std::cout << allocator.allocate(  2, 2) << ' '; allocator.print(); // note: B
	std::cout << allocator.allocate( 10   ) << ' '; allocator.print(); // note: C
	std::cout << allocator.allocate(  4   ) << ' '; allocator.print(); // note: D

	// note: A0BB 0000 | CCCC CCCC | CC00 0000 | DDDD 0000 | ...

	std::cout << allocator.allocate(988   ) << ' '; allocator.print();
	std::cout << allocator.allocate(  1   ) << ' '; allocator.print(); // note: nullptr

	return 0;
}