#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

///////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

	void make_data() 
	{
		if (m_data == nullptr) 
		{
			m_data = std::make_unique < int > (1);
		}
	}

private:

	std::unique_ptr < int > m_data;
};

///////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		Entity().make_data();
	}
	
//  ---------------------------------------------------------------------------

	{
		bool array[5]{};

		assert(sizeof(array) == std::size(array));
	}

//  ---------------------------------------------------------------------------

	{
		std::vector < bool > vector(1'000'000'000, false); 
 
		auto proxy = vector.front();

		static_assert(!std::is_same_v < decltype(proxy), bool > );

		std::cout << "main : enter char to continue : "; auto x = '\0'; std::cin >> x;
	}
}