#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>

// http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html

template < typename T >
void hash_combine(std::size_t& seed, const T& value) noexcept
{
	seed ^= std::hash < T >()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept
{
	hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types & ... args) noexcept
{
	hash_combine(seed, value);
	hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
	std::size_t seed = 0;
	hash_value(seed, args...);
	return seed;
}

class Customer
{
private:
	friend struct Customer_Hash;
	friend struct Customer_Equal;

public:
	explicit Customer(const std::string& name, const std::size_t mark) :
		m_name(name), m_mark(mark)
	{}

	~Customer() noexcept = default;

public:
	friend std::ostream& operator << (std::ostream& stream, const Customer& customer)
	{
		return (stream << customer.m_name << "," << customer.m_mark);
	}

private:
	std::string m_name;
	std::size_t m_mark;
};

struct Customer_Hash
{
	std::size_t operator() (const Customer& customer) const noexcept
	{
		return hash_value(customer.m_name, customer.m_mark);
	}
};

struct Customer_Equal
{
	bool operator() (const Customer& lhs, const Customer& rhs) const noexcept
	{
		return (lhs.m_name == rhs.m_name);
	}
};

int main(int argc, char** argv)
{
	std::unordered_set < Customer, Customer_Hash, Customer_Equal > customers;

	customers.insert(Customer("Ivan", 42));
	customers.insert(Customer("Jens", 66));

	for (const auto& customer : customers)
	{
		std::cout << customer << std::endl;
	}

	system("pause");

	return EXIT_SUCCESS;
}