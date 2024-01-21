#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

[[nodiscard]] auto create(bool b) // note: optional returned value
{
	return (b ? std::optional < std::string > ("object") : std::nullopt);
}

int main()
{
    std::optional < int > o1; // note: same as std::nullopt

    std::cout << o1.has_value() << std::endl;

    auto o2 = std::make_optional(42);

    o2.reset(); // note: same as std::nullopt

    std::optional < std::string > o3(std::in_place, 5, 'a'); // note: in-place construction

    std::cout << *o3 << ' ' << o3->front() << std::endl;

    std::cout << create(false).value_or("empty") << std::endl;

    if (auto object = create(true))
    {
        std::cout << *object << std::endl;
    }

	return 0;
}