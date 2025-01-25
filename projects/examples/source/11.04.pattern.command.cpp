#include <array>
#include <cassert>
#include <cstdint>
#include <exception>
#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{
	enum class State : std::uint8_t { slow, fast };

//  -----------------------------------------------

	State state = State::slow; 	
}; 

////////////////////////////////////////////////////////////////////////////////////

class Command
{
public:

	using State = Entity::State;
	
//  ---------------------------------------------------------------------------

	Command(Entity & entity, State state) : m_entity(entity), m_state(state) {}

//  ---------------------------------------------------------------------------

	void apply() const
	{
		m_entity.state = m_state;
	}

private:

	Entity & m_entity; State m_state = State::slow;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		using State = Entity::State;

		Entity entity_1, entity_2;

		std::vector < Command > commands = 
		{
			Command(entity_1, State::slow),

			Command(entity_2, State::fast)
		};

		for (auto command : commands) 
		{
			command.apply();
		}

		assert(entity_1.state == Entity::State::slow);

		assert(entity_2.state == Entity::State::fast);
	}
	
//  --------------------------------------------------------------------------------

	{
		using State = Entity::State;

		Entity entity;

		std::array < std::function < void(void) > , 2 > commands = 
		{
			[&entity](){ entity.state = State::slow; },
			
			[&entity](){ entity.state = State::fast; }
		};

		commands.at(0)(); assert(entity.state == State::slow);
		
		commands.at(1)(); assert(entity.state == State::fast);
	}
}