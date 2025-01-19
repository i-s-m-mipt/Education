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
	enum class Order : std::uint8_t { fast, slow };

	enum class State : std::uint8_t { fast, slow };

//  -----------------------------------------------

	State state = State::slow; 	
}; 

////////////////////////////////////////////////////////////////////////////////////

class Command
{
public:

	using Order = Entity::Order;

	using State = Entity::State;
	
//  ---------------------------------------------------------------------------

	Command(Entity & entity, Order order) : m_entity(entity), m_order(order) {}

//  ---------------------------------------------------------------------------

	void apply() const
	{
		switch (m_order)
		{
			case Order::fast: { m_entity.state = State::fast; break; }

			case Order::slow: { m_entity.state = State::slow; break; }
			
			default: 
			{
				throw std::runtime_error("invalid data");
			}
		}
	}

private:

	Entity & m_entity; Order m_order = Order::slow;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		Entity entity_1(Entity::State::slow);
		
		Entity entity_2(Entity::State::slow);

		std::vector < Command > commands = 
		{
			Command(entity_1, Entity::Order::fast), 
			Command(entity_1, Entity::Order::fast),
			Command(entity_2, Entity::Order::fast),
			Command(entity_1, Entity::Order::slow),
			Command(entity_2, Entity::Order::slow)
		};

		for (auto command : commands) 
		{
			command.apply();
		}

		assert(entity_1.state == Entity::State::slow);

		assert(entity_2.state == Entity::State::slow);
	}
	
//  --------------------------------------------------------------------------------

	{
		using Order = Entity::Order;

		using State = Entity::State;

		Entity entity(State::slow);

		std::unordered_map < Order, std::function < void(void) > > commands = 
		{
			std::make_pair(Order::fast, [&entity](){ entity.state = State::fast; }),
			
			std::make_pair(Order::slow, [&entity](){ entity.state = State::slow; })
		};

		commands.at(Order::fast)(); assert(entity.state == State::fast);
		
		commands.at(Order::slow)(); assert(entity.state == State::slow);
	}
}