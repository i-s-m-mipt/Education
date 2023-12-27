#include <string>
#include <unordered_set>

class Person
{
public:

	explicit Person(const std::string & name) : m_name(name) {}

	const auto & name() const noexcept { return m_name; }

private:

	std::string m_name;

}; // class Person

struct Hash
{
	std::size_t operator()(const Person & person) const noexcept
	{
		return std::hash < std::string > ()(person.name());
	}

}; // struct Hash

struct Equal
{
	bool operator()(const Person & lhs, const Person & rhs) const noexcept
	{
		return (lhs.name() == rhs.name());
	}

}; // struct Equal

int main()
{
	std::unordered_set < Person, Hash, Equal > persons; // note: same for other containers

	persons.emplace("Matthias");

	return 0;
}