///////////////////////////////////////////////////////////////////////////////////////

// chapter : Memory

///////////////////////////////////////////////////////////////////////////////////////

// section : Allocators

///////////////////////////////////////////////////////////////////////////////////////

// content : Linear Allocator Adapter

///////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <memory>
#include <new>
#include <print>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////////////////////////////

class Storage : private boost::noncopyable
{
public :

	Storage(std::size_t size) : m_size(size)
	{
		m_begin = operator new(m_size, std::align_val_t(s_alignment));
	}

//  ------------------------------------------------------------------------------

   ~Storage()
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

//  ------------------------------------------------------------------------------

    void deallocate(void *, std::size_t) const {}

//  ------------------------------------------------------------------------------

	void show() const
	{
		std::print
		(
			"Storage::show : m_size = {} m_begin = {:018} m_offset = {:0>4}\n",

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

///////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Allocator
{
public :

    using value_type = T;

//  -----------------------------------------------------------------------------------

    Allocator(Storage & storage) : m_storage(&storage) {}

//  -----------------------------------------------------------------------------------

    template < typename U > Allocator(Allocator < U > const & other) 
	: 
		m_storage(other.m_storage) 
	{}

//  -----------------------------------------------------------------------------------

    auto allocate(std::size_t size) const
    {
        return static_cast < T * > (m_storage->allocate(size * sizeof(T), alignof(T)));
    }

//  -----------------------------------------------------------------------------------

    void deallocate(T * x, std::size_t size) const
    {
        m_storage->deallocate(x, size * sizeof(T));
    }

private :

    Storage * m_storage = nullptr;
};

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Storage storage(1 << 10);

//  ---------------------------------------------------------

    Allocator < int > allocator(storage);

//  ---------------------------------------------------------

    std::vector < int, Allocator < int > > vector(allocator);

//  ---------------------------------------------------------

	vector = { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------------

    storage.show(); vector.push_back(1);

    storage.show();
}

///////////////////////////////////////////////////////////////////////////////////////