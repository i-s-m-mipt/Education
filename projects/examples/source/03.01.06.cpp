#include <cassert>
#include <string>

///////////////////////////////////////////////////////////////

class Entity
{
public:

	Entity(int x) : m_data(x) {}

//  -----------------------------------------------------------

    const auto & get() const
    {      
        return m_data_cache.load(*this);
    }

//  -----------------------------------------------------------

    void set(int x) 
    { 
        if (x > 0)
        {
            m_data = x;

            m_data_cache.clear();
        }
    }

private:

	class Data_Cache 
	{ 
	public:

		auto load(const Entity & entity) -> const std::string &
		{
			if (m_data.empty())
			{
				m_data = std::to_string(entity.m_data);
			}
			
			return m_data;
		}

		void clear()
		{
			m_data.clear();
		}

	private:

		std::string m_data;
	};

//  -----------------------------------------------------------

	mutable Data_Cache m_data_cache;

//  -----------------------------------------------------------

	int m_data = 0;
};

///////////////////////////////////////////////////////////////

int main()
{
    Entity entity(1);

	entity.set(2);

    assert(entity.get() == "2");
}