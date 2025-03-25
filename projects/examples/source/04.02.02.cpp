#include <deque>
#include <iterator>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename C = std::vector < T > > class Stack_v1
{
private :

	C m_container;
};

////////////////////////////////////////////////////////////////////////////////////////

template < typename T, template < typename U > typename C = std::vector > class Stack_v2
{
private :

	C < T > m_container;
};

////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	template < typename U > typename C1,
	
	template < typename U > typename C2, typename T
>		   
auto copy(const C1 < T > & container)
{
	return C2 < T > (std::begin(container), std::end(container));
}

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Stack_v1 < int, std::deque < int > > stack_v1;
	
	Stack_v2 < int, std::deque         > stack_v2;

//  -------------------------------------------------------

	std::vector vector = { 1, 2, 3, 4, 5 };

//  -------------------------------------------------------

	auto deque = copy < std::vector, std::deque > (vector);
}