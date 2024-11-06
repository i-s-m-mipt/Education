#include <cassert>
#include <cstdint>
#include <exception>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

//  ================================================================================================

struct Entity 
{
	enum class Order : std::uint8_t { fast, slow };
	enum class State : std::uint8_t { fast, slow };

//  ------------------------------------------------------------------------------------------------
	
	State state = State::slow; 	
}; 

//  ================================================================================================

class Command
{
public:

	using Order = Entity::Order;
	using State = Entity::State;
	
//  -------------------------------------------------------------------------------------

	explicit Command(Entity & entity, Order order) : m_entity(entity), m_order(order) {}

//  -------------------------------------------------------------------------------------

	void apply() const
	{
		switch (m_order)
		{
			case Order::fast: { m_entity.state = State::fast; break; }
			case Order::slow: { m_entity.state = State::slow; break; }
			
			[[unlikely]] default: 
			{
				throw std::runtime_error("invalid order");
			}
		}
	}

private:

	Entity & m_entity; Order m_order = Order::slow;
};

//  ================================================================================================

int main()
{
	Entity entity_1;
	Entity entity_2;

	using Order = Entity::Order;

	std::vector < Command > commands_1
	(
		{
			Command(entity_1, Order::fast), 
			Command(entity_1, Order::fast),
			Command(entity_2, Order::fast),
			Command(entity_1, Order::slow),
			Command(entity_2, Order::slow)
		}
	);

	for (auto command : commands_1) 
	{
		command.apply();
	}

	assert(entity_1.state == Entity::State::slow);
	assert(entity_2.state == Entity::State::slow);

//  ----------------------------------------------

	Entity entity_3;

	std::unordered_map < Order, std::function < void(void) > > commands_2
	(
		{
			std::make_pair(Order::fast, [&entity_3](){ entity_3.state = Entity::State::fast; }),
			std::make_pair(Order::slow, [&entity_3](){ entity_3.state = Entity::State::slow; })
		}
	);

	commands_2.at(Order::fast)(); assert(entity_3.state == Entity::State::fast);
	commands_2.at(Order::slow)(); assert(entity_3.state == Entity::State::slow);
}