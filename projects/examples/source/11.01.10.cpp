#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

///////////////////////////////////////////////////////////////////////////////

struct Entity 
{
	enum class State : std::uint8_t { slow, fast };

//  -----------------------------------------------

	State state = State::slow;
};

///////////////////////////////////////////////////////////////////////////////

class Command
{
public:

	using State = Entity::State;
	
//  ---------------------------------------------------------------------------

	Command(Entity & entity, State state) : m_entity(entity), m_state(state) {}

//  ---------------------------------------------------------------------------

	void operator()() const
	{
		m_entity.state = m_state;
	}

private:

	Entity & m_entity;
	
	State m_state = State::slow;
};

///////////////////////////////////////////////////////////////////////////////

int main()
{
	using State = Entity::State;

//  --------------------------------------------------------

	Entity entity;

//  --------------------------------------------------------

	std::vector < Command > commands_1 = 
	{
		Command(entity, State::slow),

		Command(entity, State::fast)
	};

//  --------------------------------------------------------

	commands_1.at(0)(); assert(entity.state == State::slow);

	commands_1.at(1)(); assert(entity.state == State::fast);
	
//  --------------------------------------------------------

	std::vector < std::function < void() > > commands_2 = 
	{
		[&entity](){ entity.state = State::slow; },
			
		[&entity](){ entity.state = State::fast; }
	};

//  --------------------------------------------------------

	commands_2.at(0)(); assert(entity.state == State::slow);
		
	commands_2.at(1)(); assert(entity.state == State::fast);
}