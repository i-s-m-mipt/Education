#include <memory>

//////////////////////////////////////////////////

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

//////////////////////////////////////////////////

int main()
{
    Entity().make_data();
}