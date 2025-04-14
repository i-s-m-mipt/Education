//////////////////////////////////////////////////////////////

#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////

class Entity
{
public :

	Entity(int x) : m_x(x) {}

//  ----------------------------------------------------------

    auto const & get() const
    {      
        return m_cache.get(*this);
    }

//  ----------------------------------------------------------

    void set(int x) 
    {
        if (x > 0)
        {
            m_x = x;

            m_cache.clear();
        }
    }

private :

	class Cache 
	{
	public :

		auto get(Entity const & entity) -> std::string const &
		{
			if (m_string.empty())
			{
				m_string = std::to_string(entity.m_x);
			}
			
			return m_string;
		}

	//  ------------------------------------------------------

		void clear()
		{
			m_string.clear();
		}

	private :

		std::string m_string;
	};

//  ----------------------------------------------------------

	int m_x = 0;

//  ----------------------------------------------------------

	mutable Cache m_cache;
};

//////////////////////////////////////////////////////////////

int main()
{
    Entity entity(1);

//  ----------------------------

    assert(entity.get() == "1");

	assert(entity.get() == "1");

//  ----------------------------

	entity.set(2);

//  ----------------------------

	assert(entity.get() == "2");
}

//////////////////////////////////////////////////////////////