#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/noncopyable.hpp>

// =================================================================================================

class Arena : private boost::noncopyable // note: no deallocations for blocks of different sizes
{
public:

	explicit Arena(std::size_t size) : m_size(size)
	{
		m_begin = ::operator new(m_size, default_alignment);
	}

   ~Arena() noexcept
	{
		::operator delete(m_begin, default_alignment);
	}

	[[nodiscard]] void * allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t))
	{
		void * first = get_byte(m_begin) + m_offset;

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first) // note: modifies first and space
		{
			m_offset = m_size - space + size; 
			
			return first; // note: aligned pointer
		}
		else throw std::bad_alloc(); // note: throwing exception instead of returning nullptr
	}

    void deallocate(void *, std::size_t) const noexcept {}

	void print() const
	{
		std::cout << m_begin << ": ";

		std::cout << std::setw(4) << std::right << std::setfill('0') << m_offset;

		std::cout << " / " << m_size << std::endl;
	}

private:

	[[nodiscard]] std::byte * get_byte(void * ptr) const noexcept
	{
		return static_cast < std::byte * > (ptr);
	}

public:

	static constexpr std::align_val_t default_alignment { alignof(std::max_align_t) };

private:
	
	const std::size_t m_size;

private:

	std::size_t m_offset = 0;

	void * m_begin = nullptr;

}; // class Arena_Allocator : private boost::noncopyable

// =================================================================================================

template < typename T > class Allocator
{
public:

    using value_type = T;

public:

    explicit Allocator(Arena & arena) noexcept : m_arena(&arena) {}

    template < typename U > Allocator(const Allocator < U > & other) : m_arena(other.m_arena) {}

    [[nodiscard]] T * allocate(std::size_t size) const noexcept
    { 
        return static_cast < T * > (m_arena->allocate(size * sizeof(T), alignof(T))); 
    }

    void deallocate(T * ptr, std::size_t size) const noexcept
    {
        m_arena->deallocate(ptr, size * sizeof(T)); 
    }

private:

    Arena * const m_arena = nullptr;

}; // template < typename T > class Allocator

// =================================================================================================

int main()
{
	Arena arena(1024);

    Allocator < int > allocator(arena);

    arena.print(); // note: 0 bytes used

    std::vector < int, Allocator < int > > vector(10, 42, allocator);

    arena.print(); // note: 40 bytes used

    vector.push_back(42);

    arena.print(); // note: 128 bytes used

	return 0;
}