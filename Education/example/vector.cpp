#include <iostream>
#include <string>
#include <vector>
#include <exception>

void print(std::vector < double > v)
{
    for (auto i = std::begin(v); i != std::end(v); ++i)
    {
        std::cout << *i << ' ';
    }

    std::cout << std::endl;
}

int main()
{
    std::vector < double >      v_1(10, 0.0);
    std::vector < int >         v_2({ 7, -42, 5, 0, 16, -8 });
    std::vector < std::string > v_3({ "Red", "Green", "Blue" });
    std::vector < double >      v_4(v_1);

    for (std::size_t i = 0; i < v_1.size(); ++i)
    {
        std::cout << v_1[i] << ' ';
    }

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;

    std::cout << v_2.front() << std::endl;
    std::cout << v_2.back() << std::endl;
    std::cout << std::boolalpha << std::empty(v_2) << std::endl;

    std::cout << "========================================" << std::endl;

    std::vector < double > v_5(10, 1.0);

    v_1 = v_5;
    std::swap(v_4, v_5);

    print(v_1);
    print(v_4);
    print(v_5);

    std::cout << "========================================" << std::endl;

    v_3.push_back("Yellow");
    std::cout << v_3.back() << std::endl;
    v_3.pop_back();
    std::cout << v_3.back() << std::endl;
    v_1.clear();
    std::cout << std::boolalpha << std::empty(v_1) << std::endl;

    std::cout << "========================================" << std::endl;

    v_1.insert(std::begin(v_1), 10, 0.0);
    print(v_1);
    v_1.insert(std::next(std::begin(v_1), 2), 1000.0);
    print(v_1);
    v_1.insert(std::begin(v_1), std::begin(v_4), std::next(std::begin(v_4), 5));
    print(v_1);

    std::cout << "========================================" << std::endl;

    v_1.emplace(std::begin(v_1), 2.0);
    print(v_1);
    v_1.emplace_back(99.0);
    print(v_1);

    std::cout << "========================================" << std::endl;

    v_1.erase(std::next(std::begin(v_1), 3));
    print(v_1);
    v_1.erase(std::begin(v_1), std::next(std::begin(v_1), 5));
    print(v_1);

    std::cout << "========================================" << std::endl;

    return 0;
}