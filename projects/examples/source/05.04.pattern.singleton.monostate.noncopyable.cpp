#include <iostream>

#include <boost/noncopyable.hpp>

//  ================================================================================================

class Singleton // support: реализация Скотта Мейерса
{
private:

    Singleton() = default;

public:

    Singleton            (const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;

public:

    [[nodiscard]] int data() const { return m_data; }

public:

    [[nodiscard]] static Singleton & get_instance() { static Singleton instance; return instance; }

private:

    const int m_data = 42; 
    
}; // class Singleton 

//  ================================================================================================

class Monostate
{
public:

    void update(int new_data) { m_data = new_data; }

    [[nodiscard]] int data() const { return m_data; }

private:

    static inline int m_data = 42; 
    
}; // class Monostate

//  ================================================================================================

class Noncopyable
{
protected:

    Noncopyable() = default;

    Noncopyable            (const Noncopyable &) = delete;
    Noncopyable & operator=(const Noncopyable &) = delete;

   ~Noncopyable() = default;

}; // class Noncopyable

//  ================================================================================================

class Unique : private Noncopyable // support: класс boost::noncopyable
{
public:

    [[nodiscard]] constexpr int data() const { return m_data; }

private:

    const int m_data = 42; 
    
}; // class Unique : private Noncopyable

//  ================================================================================================

int main()
{
    const auto & singleton = Singleton::get_instance();

    std::cout << singleton.data() << std::endl;

//  ================================================================================================

    Monostate monostate_1;
    Monostate monostate_2; 
    Monostate monostate_3; 

    monostate_3.update(42);

    std::cout << monostate_1.data() << std::endl;
    std::cout << monostate_2.data() << std::endl;
    std::cout << monostate_3.data() << std::endl;

//  ================================================================================================

    const Unique unique_1;
//  const Unique unique_2 = unique_1; // error

    std::cout << unique_1.data() << std::endl;

    return 0;
}