#include <iostream>
#include <string>
#include <unordered_set>

class Person
{
public:

	explicit Person(const std::string & name) : m_name(name) {}

	[[nodiscard]] const auto & name() const noexcept { return m_name; }

private:

	std::string m_name;

}; // class Person

struct Hash
{
	[[nodiscard]] auto operator()(const Person & person) const noexcept
	{
		return std::hash < std::string > ()(person.name());
	}

}; // struct Hash

struct Equal
{
	[[nodiscard]] auto operator()(const Person & lhs, const Person & rhs) const noexcept
	{
		return (lhs.name() == rhs.name());
	}

}; // struct Equal

int main()
{
	std::cout << Hash()(Person("Matthias")) << std::endl;

	std::unordered_set < Person, Hash, Equal > persons; // note: same for other containers

	persons.emplace("Matthias");

	return 0;
}