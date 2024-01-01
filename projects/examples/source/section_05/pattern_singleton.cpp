#include <iostream>

#include <boost/noncopyable.hpp>

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

    Singleton            (const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;

public:

    auto data() const { return m_data; }

private:

    int m_data;

}; // class Singleton 

class noncopyable // good: better than singleton
{
protected:

    noncopyable() = default;

    noncopyable            (const noncopyable &) = delete;
    noncopyable & operator=(const noncopyable &) = delete;

    ~noncopyable() = default; // note: non-polymorphic class

}; // class noncopyable

class Unique : noncopyable {}; // note: consider boost::noncopyable

int main()
{
    std::cout << Singleton::get_instance().data() << std::endl;

    [[maybe_unused]] Unique u1;

//  Unique u2 = u1; // error: noncopyable type

    return 0;
}