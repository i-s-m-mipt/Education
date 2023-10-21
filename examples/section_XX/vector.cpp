#include <iostream>
#include <string>
#include <vector>

void print(const std::vector < double > & v)
{
    for (auto i = 0; i < std::size(v); ++i)
    {
        std::cout << v[i] << (i + 1 == std::size(v) ? '\n' : ' ');
    }
}

int main()
{
    std::vector < double > v1;

    std::vector < double > v2(10, 0.0);

    std::vector < int > v3({ 7, -42, 5, 0, 16, -8 });

    std::vector < std::string > v4({ "Red", "Green", "Blue" });

    std::cout << "========================================" << std::endl;

    std::cout << v2.front() << ' ' << v2.back() << std::endl;

    std::cout << std::empty(v2) << std::endl;

    print(v2);

    std::cout << "========================================" << std::endl;

    std::vector < double > v5(v2);

    v1 = v5;

    print(v1);

    std::cout << "========================================" << std::endl;

    v1.push_back(2.0);

    std::cout << v1.back() << std::endl;

    v1.pop_back();

    std::cout << v1.back() << std::endl;

    v1.clear();

    std::cout << std::empty(v1) << std::endl;

    std::cout << "========================================" << std::endl;

    v1.insert(std::begin(v1), 10, 2.0);
    print(v1);
    v1.insert(std::next(std::begin(v1), 2), 3.0);
    print(v1);
    v1.insert(std::begin(v1), std::begin(v5), std::next(std::begin(v5), 5));
    print(v1);

    std::cout << "========================================" << std::endl;

    v1.erase(std::next(std::begin(v1), 3));
    print(v1);
    v1.erase(std::begin(v1), std::next(std::begin(v1), 5));
    print(v1);

    std::cout << "========================================" << std::endl;

    return 0;
}