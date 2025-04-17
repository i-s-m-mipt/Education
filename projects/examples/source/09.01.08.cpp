/////////////////////////////////////////////////////////

#include <cstddef>
#include <utility>

/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

/////////////////////////////////////////////////////////

class Controller : private boost::noncopyable
{
public :

    void increase() 
    { 
        ++m_counter; 
    }

    void decrease() 
    { 
        if (--m_counter == 0) 
        {
            clear();
        }
    }

protected :

             Controller() = default;

    virtual ~Controller() = default;

private :

    virtual void clear() = 0;

//  --------------------------------

    std::size_t m_counter = 0;
};

/////////////////////////////////////////////////////////

template < typename T > class Handler : public Controller
{
public :

    Handler(T * x) : m_x(x)
    {
        increase();
    }

private :

    void clear() override
    {
        if (m_x)
        {
            delete m_x;
        }
            
        delete this;
    }

//  -----------------------

    T * m_x = nullptr;
};

/////////////////////////////////////////////////////////

template < typename T > class Shared
{
public :

    Shared(T * x = nullptr) : m_x(x)
    {
        if (m_x)
        {
            m_controller = new Handler < T > (m_x);
        }
    }

//  ----------------------------------------------------

    Shared(Shared < T > const & other) 
    : 
        m_x(other.m_x), m_controller(other.m_controller)
    {
        if (m_controller) 
        {
            m_controller->increase();
        }
    }

//  ----------------------------------------------------

    Shared(Shared < T > && other) : Shared()
	{
		swap(other);
	}

//  ----------------------------------------------------

   ~Shared() 
    { 
        if (m_controller) 
        {
            m_controller->decrease();
        } 
    }

//  ----------------------------------------------------

    auto & operator=(Shared other)
    {
        swap(other);

    //  -------------
        
        return *this;
    }

//  ----------------------------------------------------

    void swap(Shared & other)
    {
        std::swap(m_x, other.m_x);

        std::swap(m_controller, other.m_controller);
    }

private :

    T * m_x = nullptr;

//  ----------------------------------------------------
    
    Controller * m_controller = nullptr;
};

/////////////////////////////////////////////////////////

int main()
{
    Shared < int > shared_1;

    Shared < int > shared_2(new auto(2));

    Shared < int > shared_3 = shared_2;

    Shared < int > shared_4 = std::move(shared_3);

//  ----------------------------------------------

    shared_3 = shared_2;

    shared_4 = std::move(shared_3);
}

/////////////////////////////////////////////////////////