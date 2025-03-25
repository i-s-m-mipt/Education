#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////

template < typename T > class RAII : private boost::noncopyable
{
public :

	RAII(T x) : m_x(new T(x)) {}

   ~RAII() 
	{ 
		if (m_x) 
		{
			delete m_x;
		}
	}

private :

	T * m_x = nullptr;
};

///////////////////////////////////////////////////////////////

int main()
{
    RAII < int > raii(1);
}