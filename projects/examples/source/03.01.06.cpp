//////////////////////////////////////////////////////////////

#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////

class Entity
{
public :

	Entity(int x) : m_x(x) {}

//  ----------------------------------------------------------

    const auto & get() const
    {      
        return m_cache.get(*this);
    }

//  ----------------------------------------------------------

    void set(int x) 
    {
        if (x > 0)
        {
            m_x = x;

		//  ----------------

            m_cache.clear();
        }
    }

private :

	class Cache 
	{
	public :

		auto get(const Entity & entity) -> const std::string &
		{
			if (m_string.empty())
			{
				m_string = std::to_string(entity.m_x);
			}

		//  ------------------------------------------
			
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

	mutable Cache m_cache;

//  ----------------------------------------------------------

	int m_x = 0;
};

//////////////////////////////////////////////////////////////

int main()
{
    Entity entity(1);

//  ----------------------------

	entity.set(2);

//  ----------------------------

    assert(entity.get() == "2");
}

//////////////////////////////////////////////////////////////