#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <stdexcept>

template < typename T >
class Threadsafe_Stack
{
public:

	Threadsafe_Stack() = default;

	Threadsafe_Stack(const Threadsafe_Stack & other)
	{
		std::lock_guard < std::mutex > lock(other.m_mutex);
		m_data = other.m_data;
	}

	Threadsafe_Stack& operator=(const Threadsafe_Stack &) = delete;

public:

	void push(T value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_data.push(value);
	}

	std::shared_ptr < T > pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_data.empty())
		{
			throw std::range_error("empty stack");
		}

		const auto result = std::make_shared < T > (m_data.top());
		m_data.pop();

		return result;
	}

	void pop(T & value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_data.empty())
		{
			throw std::range_error("empty stack");
		}

		value = m_data.top();
		m_data.pop();
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_data.empty();
	}

private:

	std::stack < T > m_data;

private:

	mutable std::mutex m_mutex;
};

int main(int argc, char ** argv)
{
	Threadsafe_Stack < int > stack;

	stack.push(5);
	stack.pop();

	if (!stack.empty())
	{
		int x;
		stack.pop(x);
	}

	system("pause");

	return EXIT_SUCCESS;
}
