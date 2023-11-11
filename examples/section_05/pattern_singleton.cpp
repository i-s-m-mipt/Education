#include <iostream>

class Singleton // bad: single responsibility principle violation
{
public:

    static auto & get_instance() // note: once initialized global state
    {
        static Singleton instance; // good: guaranteed to be destroyed

        return instance; // good: return by reference, not pointer
    }

private:

    Singleton() = default;

public: // good: deleted special member functions are public

    Singleton            (const Singleton & other) = delete;
    Singleton & operator=(const Singleton & other) = delete;

public:

    auto data() const { return m_data; }

private:

    int m_data;

}; // class Singleton 

int main()
{
    std::cout << Singleton::get_instance().data() << std::endl;

    return 0;
}