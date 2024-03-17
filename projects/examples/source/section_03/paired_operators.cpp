#include <iostream>
#include <vector>

class Data 
{
public:

    explicit Data(std::size_t size, int value) : m_data(size, value) {}

    [[nodiscard]] const auto & operator[](std::size_t index) const 
    {
        std::cout << "Data::operator[] const" << std::endl;

        return m_data[index];
    }

    [[nodiscard]] auto & operator[](std::size_t index) // good: calls constant version
    {
        std::cout << "Data::operator[]" << std::endl;

        return const_cast < int & > (static_cast < const Data & > (*this)[index]);
    }

private:

    std::vector < int > m_data;

}; // class Data

int main()
{
    std::cout << Data(1, 42)[0] << std::endl;

    return 0;
}