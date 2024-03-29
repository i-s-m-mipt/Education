#include <iostream>

#include <boost/noncopyable.hpp>

class Singleton // bad: single responsibility principle violation
{
public:

    [[nodiscard]] static Singleton & get_instance() // note: once initialized
    {
        static Singleton instance; // good: guaranteed to be destroyed

        return instance; // good: return by reference, not pointer (old)
    }

private:

    Singleton() = default;

public: // good: deleted special member functions are public

    Singleton            (const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;

public:

    [[nodiscard]] int data() const { return m_data; }

private:

    int m_data = 0;

}; // class Singleton 

class Monostate // good: better than singleton
{
public:

    void update(int new_data) { m_data = new_data; }

    [[nodiscard]] int data() const { return m_data; }

private:

    static inline int m_data = 0; // note: shared data for all instances

}; // class Monostate

class Noncopyable // good: better than singleton
{
protected:

     Noncopyable() = default;

     Noncopyable            (const Noncopyable &) = delete;
     Noncopyable & operator=(const Noncopyable &) = delete;

    ~Noncopyable() = default; // note: non-polymorphic class

}; // class Noncopyable

class Unique : private Noncopyable // note: consider boost::noncopyable
{
public:

    [[nodiscard]] constexpr int data() const { return m_data; }

private:

    int m_data = 0;

}; // class Unique : private Noncopyable

int main()
{
    const auto & singleton = Singleton::get_instance(); // note: single instance

    std::cout << singleton.data() << std::endl;

    Monostate monostate_1; // note: allowed multiple instances creation
    Monostate monostate_2; 
    Monostate monostate_3; 

    monostate_3.update(42); // note: shared data for all instances 

    std::cout << monostate_1.data() << std::endl;
    std::cout << monostate_2.data() << std::endl;
    std::cout << monostate_3.data() << std::endl;

    const Unique unique_1;

//  const Unique unique_2 = unique_1; // error: noncopyable type

    std::cout << unique_1.data() << std::endl;

    return 0;
}