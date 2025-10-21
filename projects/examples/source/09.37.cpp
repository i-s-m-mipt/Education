////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <format>
#include <memory>
#include <new>
#include <print>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////

class Arena : private boost::noncopyable
{
public :

	Arena(std::size_t size) : m_size(size)
	{
		m_begin = operator new(m_size, std::align_val_t(s_alignment));
	}

//  ------------------------------------------------------------------------------

   ~Arena()
	{
		operator delete(m_begin, m_size, std::align_val_t(s_alignment));
	}

//  ------------------------------------------------------------------------------

	auto allocate(std::size_t size, std::size_t alignment = s_alignment) -> void *
	{
		void * begin = get_byte(m_begin) + m_offset;

		auto free = m_size - m_offset;

		if (begin = std::align(alignment, size, begin, free); begin)
		{
			m_offset = m_size - free + size;
			
			return begin;
		}
		else 
		{
			return nullptr;
		}
	}

    void deallocate(void *, std::size_t) const {}

//  ------------------------------------------------------------------------------

	void show() const
	{
		std::print
		(
			"Arena::show : m_size = {} m_begin = {:018} m_offset = {:0>4}\n",

			m_size, m_begin, m_offset
		);
	}

private :

	auto get_byte(void * x) const -> std::byte *
	{
		return static_cast < std::byte * > (x);
	}

//  ------------------------------------------------------------------------------

	std::size_t m_size = 0, m_offset = 0;

	void * m_begin = nullptr;

//  ------------------------------------------------------------------------------

	static inline auto s_alignment = alignof(std::max_align_t);
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Allocator
{
public :

    using value_type = T;

//  --------------------------------------------------------------------------------------------

    Allocator(Arena & arena) : m_arena(&arena) {}

//  --------------------------------------------------------------------------------------------

    template < typename U > Allocator(Allocator < U > const & other) : m_arena(other.m_arena) {}

//  --------------------------------------------------------------------------------------------

    auto allocate(std::size_t size) const
    { 
        return static_cast < T * > (m_arena->allocate(size * sizeof(T), alignof(T)));
    }

//  --------------------------------------------------------------------------------------------

    void deallocate(T * x, std::size_t size) const
    {
        m_arena->deallocate(x, size * sizeof(T));
    }

private :

    Arena * m_arena = nullptr;
};

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Arena arena(1'024);

//  ----------------------------------------------------------------------------

    Allocator < int > allocator(arena);

//  ----------------------------------------------------------------------------

    std::vector < int, Allocator < int > > vector({ 1, 2, 3, 4, 5 }, allocator);

//  ----------------------------------------------------------------------------

    arena.show(); vector.push_back(1);
	
    arena.show();
}

////////////////////////////////////////////////////////////////////////////////////////////////