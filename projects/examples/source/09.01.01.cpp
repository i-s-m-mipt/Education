#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////

template < typename T > class RAII : private boost::noncopyable
{
public:

	RAII(T x) : m_data(new T(x)) {}

   ~RAII() 
	{ 
		if (m_data) 
		{
			delete m_data;
		}
	}

private:

	T * m_data = nullptr;
};

///////////////////////////////////////////////////////////////

int main()
{
    RAII < int > raii(1);
}