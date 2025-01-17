#include <cassert>
#include <cstddef>
#include <utility>

#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    class RCCB_base : private boost::noncopyable
    {
    public:

        void increase() { ++m_counter; }

        void decrease() 
        { 
            if (--m_counter == 0) 
            {
                clear(); 
            }
        }

    protected:

                 RCCB_base() = default;

        virtual ~RCCB_base() = default;

    private:

        virtual void clear() = 0;

    //  ----------------------------------------

        std::size_t m_counter = 0;
    };
}

///////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    template < typename T > class RCCB : public RCCB_base
    {
    public:

        RCCB(T * data) : m_data(data)
        {
            increase();
        }

    private:

        void clear() override
        {
            if (m_data)
            {
                delete m_data;
            }
            
            delete this;
        }

//      -------------------------------------------------

        T * m_data = nullptr;
    };
}

///////////////////////////////////////////////////////////////////////////////////

template < typename T > class Shared
{
public:

    Shared(T * data = nullptr) : m_data(data)
    {
        if (m_data)
        {
            m_rccb = new detail::RCCB < T > (m_data);
        }
    }

    Shared(const Shared < T > & other) : m_data(other.m_data), m_rccb(other.m_rccb)
    {
        if (m_rccb) 
        {
            m_rccb->increase();
        }
    }

    Shared(Shared < T > && other) : Shared()
	{
		swap(other);
	}

    auto & operator=(const Shared & other)
    {
        Shared(other).swap(*this); 
        
        return *this;
    }

    auto & operator=(Shared && other)
    {
        Shared(std::move(other)).swap(*this); 
        
        return *this;
    }

   ~Shared() 
    { 
        if (m_rccb) 
        {
            m_rccb->decrease();
        } 
    }

//  -------------------------------------------------------------------------------

    void swap(Shared & other)
    {
        std::swap(m_data, other.m_data);

        std::swap(m_rccb, other.m_rccb);
    }

//  -------------------------------------------------------------------------------

    auto & operator*() const
    { 
        return *m_data; 
    }

private:

    T * m_data = nullptr; detail::RCCB_base * m_rccb = nullptr;
};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        Shared < int > shared_1;

        Shared < int > shared_2(new auto(2));

        Shared < int > shared_3(shared_2);

        Shared < int > shared_4(std::move(shared_3));

        shared_3 = shared_2;
        
        shared_4 = std::move(shared_3);
    }

//  -------------------------------------------------

    {
        assert(*Shared < int > (new auto(1)) == 1);
    }
}