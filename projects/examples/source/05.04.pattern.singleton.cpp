#include <cassert>
#include <iostream>

#include <boost/noncopyable.hpp>

//  ================================================================================================

class Singleton
{
private:

    Singleton() = default;
   ~Singleton() = default;

public:

    Singleton            (const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;

//  --------------------------------------------------

    static auto & instance() 
    { 
        static Singleton singleton; 
        
        return singleton; 
    }

//  ---------------------

    void test() const
    { 
        std::clog << "Singleton::test\n"; 
    }
};

//  ================================================================================================

class Noncopyable
{
protected:

    Noncopyable() = default;
   ~Noncopyable() = default;

public:

    Noncopyable            (const Noncopyable &) = delete;
    Noncopyable & operator=(const Noncopyable &) = delete;
};

//  ================================================================================================

struct Unique_v1 : private        Noncopyable {};
struct Unique_v2 : private boost::noncopyable {};

//  ================================================================================================

int main()
{
    Singleton::instance().test();

//  ---------------------------------------

    [[maybe_unused]] Unique_v1 unique_v1_1;

//  [[maybe_unused]] Unique_v1 unique_v1_2 = unique_v1_1; // error

    [[maybe_unused]] Unique_v2 unique_v2_1;

//  [[maybe_unused]] Unique_v2 unique_v2_2 = unique_v2_1; // error
}