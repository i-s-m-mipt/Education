#include <cstddef>
#include <exception>
#include <format>
#include <iomanip>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <vector>

#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////

class Arena : private boost::noncopyable
{
public:

	explicit Arena(std::size_t size) : m_size(size)
	{
		m_begin = operator new(m_size, std::align_val_t(default_alignment));
	}

   ~Arena()
	{
		if (m_begin)
		{
			operator delete(m_begin, m_size, std::align_val_t(default_alignment));
		}
	}

//  ------------------------------------------------------------------------------------

	auto allocate(std::size_t size, std::size_t alignment = default_alignment) -> void *
	{
		void * first = get_byte(m_begin) + m_offset;

		auto space = m_size - m_offset;

		if (first = std::align(alignment, size, first, space); first)
		{
			m_offset = m_size - space + size; 
			
			return first;
		}
		else 
		{
			return nullptr;
		}
	}

    void deallocate(void * , std::size_t) const {}

//  ------------------------------------------------------------------------------------

	void test() const
	{
		std::cout << "Arena::test : ";

		std::cout << "m_size = " << m_size << ' ';

		std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';

		std::cout << "m_offset = " << std::setw(4) << std::setfill('0') << std::right;
		
		std::cout <<  m_offset << '\n';
	}

private:

	auto get_byte(void * ptr) const -> std::byte *
	{
		return static_cast < std::byte * > (ptr);
	}

//  ------------------------------------------------------------------------------------

	std::size_t m_size = 0, m_offset = 0;

	void * m_begin = nullptr;

//  ------------------------------------------------------------------------------------

	static inline auto default_alignment = alignof(std::max_align_t);
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Allocator
{
public:

    using value_type = T;

//  --------------------------------------------------------------------------------------------

    explicit Allocator(Arena & arena) : m_arena(&arena) {}

    template < typename U > Allocator(const Allocator < U > & other) : m_arena(other.m_arena) {}

//  --------------------------------------------------------------------------------------------

    auto allocate(std::size_t size) const
    { 
        return static_cast < T * > (m_arena->allocate(size * sizeof(T), alignof(T))); 
    }

    void deallocate(T * ptr, std::size_t size) const
    {
        m_arena->deallocate(ptr, size * sizeof(T)); 
    }

private:

    Arena * m_arena = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Arena arena(1'024);

    Allocator < int > allocator(arena);

    arena.test();

    std::vector < int, Allocator < int > > vector(5, 0, allocator);

    arena.test(); vector.push_back(1);
    arena.test();
}