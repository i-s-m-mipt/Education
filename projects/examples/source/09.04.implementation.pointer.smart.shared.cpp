#include <cassert>
#include <cstddef>
#include <utility>

#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    class Controller : private boost::noncopyable
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

                 Controller() = default;

        virtual ~Controller() = default;

    private:

        virtual void clear() = 0;

    //  ----------------------------------------

        std::size_t m_counter = 0;
    };
}

///////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    template < typename T > class Handler : public Controller
    {
    public:

        Handler(T * ptr) : m_data(ptr)
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

    Shared(T * ptr = nullptr) : m_data(ptr)
    {
        if (m_data)
        {
            m_controller = new detail::Handler < T > (m_data);
        }
    }

    Shared(const Shared < T > & other) 
    : 
        m_data(other.m_data), m_controller(other.m_controller)
    {
        if (m_controller) 
        {
            m_controller->increase();
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
        if (m_controller) 
        {
            m_controller->decrease();
        } 
    }

//  -------------------------------------------------------------------------------

    void swap(Shared & other)
    {
        std::swap(m_data, other.m_data);

        std::swap(m_controller, other.m_controller);
    }

//  -------------------------------------------------------------------------------

    auto & operator*() const
    { 
        return *m_data; 
    }

private:

    T * m_data = nullptr; detail::Controller * m_controller = nullptr;
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