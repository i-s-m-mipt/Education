#include <cassert>
#include <exception>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// =================================================================================================

struct Computer { enum class State { stop, slow, fast } state = State::stop; };

// =================================================================================================

enum class Command // note: alternative version based on classes hierarchy
{
	stop,
	slow,
	fast,

}; // enum class Command

// =================================================================================================

class Executor
{
public:

	void execute() const
	{
		switch (m_command)
		{
			case Command::stop: m_computer.state = Computer::State::stop; break;
			case Command::slow: m_computer.state = Computer::State::slow; break;
			case Command::fast: m_computer.state = Computer::State::fast; break;

			default: throw std::invalid_argument("invalid command: " + std::to_string(static_cast < int > (m_command)));
		}
	}

	Computer & m_computer; Command m_command;

}; // class Executor

// =================================================================================================

int main()
{
	Computer computer_1;
	Computer computer_2;

	std::vector < Executor > executors =
	{
		{ computer_1, Command::slow },
		{ computer_1, Command::fast },
		{ computer_2, Command::slow },
		{ computer_1, Command::stop },
		{ computer_2, Command::stop }
	};

	for (const auto & executor : executors) executor.execute();

	assert(computer_1.state == Computer::State::stop);
	assert(computer_2.state == Computer::State::stop);

	Computer computer_3;

	std::unordered_map < Command, std::function < void(void) > > commands =
	{
		{ Command::stop, [&computer_3](){ computer_3.state = Computer::State::stop; }},
		{ Command::slow, [&computer_3](){ computer_3.state = Computer::State::slow; }},
		{ Command::fast, [&computer_3](){ computer_3.state = Computer::State::fast; }}
	};

	commands.at(Command::slow)(); assert(computer_3.state == Computer::State::slow);
	commands.at(Command::fast)(); assert(computer_3.state == Computer::State::fast);
	commands.at(Command::slow)(); assert(computer_3.state == Computer::State::slow);
	commands.at(Command::stop)(); assert(computer_3.state == Computer::State::stop);

	return 0;
}