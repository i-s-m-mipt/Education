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

    int m_data = 0;

}; // class Singleton 

class Monostate // good: better than singleton
{
public:

    void update(int new_data) { m_data = new_data; }

    auto data() const { return m_data; }

private:

    static inline int m_data = 0; // note: shared data for all instances

}; // class Monostate

class Noncopyable // good: better than singleton
{
protected:

    Noncopyable() = default;

protected:

    Noncopyable            (const Noncopyable &) = delete;
    Noncopyable & operator=(const Noncopyable &) = delete;

protected:

    ~Noncopyable() = default; // note: non-polymorphic class

}; // class Noncopyable

class Unique : Noncopyable // note: consider boost::noncopyable
{
public:

    auto data() const { return m_data; }

private:

    int m_data = 0;

}; // class Unique : Noncopyable

int main()
{
    auto & singleton = Singleton::get_instance(); // note: single instance

    std::cout << singleton.data() << std::endl; // note: outputs 0

    Monostate monostate_1; // note: allowed multiple instances creation
    Monostate monostate_2; 
    Monostate monostate_3; 

    monostate_3.update(42); // note: shared data for all instances 

    std::cout << monostate_1.data() << std::endl; // note: outputs 42
    std::cout << monostate_2.data() << std::endl; // note: outputs 42
    std::cout << monostate_3.data() << std::endl; // note: outputs 42

    Unique unique_1;

//  Unique unique_2 = unique_1; // error: noncopyable type

    std::cout << unique_1.data() << std::endl; // note: outputs 0

    return 0;
}