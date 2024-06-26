#include <iostream>
#include <string>
#include <unordered_set>

//  ================================================================================================

class Person
{
public:

	constexpr explicit Person(const std::string & name) : m_name(name) {}

	[[nodiscard]] constexpr const std::string & name() const noexcept { return m_name; }

private:

	const std::string m_name;

}; // class Person

//  ================================================================================================

struct Hash
{
	[[nodiscard]] std::size_t operator()(const Person & person) const noexcept
	{
		return std::hash < std::string > ()(person.name());
	}

}; // struct Hash

//  ================================================================================================

struct Equal
{
	[[nodiscard]] bool operator()(const Person & lhs, const Person & rhs) const noexcept
	{
		return (lhs.name() == rhs.name());
	}

}; // struct Equal

//  ================================================================================================

int main()
{
	std::cout << Hash()(Person("Matthias")) << std::endl;

	std::unordered_set < Person, Hash, Equal > persons;

	persons.emplace("Matthias");

	return 0;
}