#include <cassert>
#include <iostream>

#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////////////////////////////////////

class Singleton
{
public:

    Singleton            (const Singleton &) = delete;

    Singleton & operator=(const Singleton &) = delete;

//  --------------------------------------------------

    void test() const
    { 
        std::clog << "Singleton::test\n"; 
    }

//  --------------------------------------------------

    static auto & instance() 
    { 
        static Singleton singleton; 
        
        return singleton; 
    }

private:

    Singleton() = default;
};

////////////////////////////////////////////////////////////////////////////////////////

class Noncopyable
{
public:

    Noncopyable            (const Noncopyable &) = delete;

    Noncopyable & operator=(const Noncopyable &) = delete;

protected:

    Noncopyable() = default;
};

////////////////////////////////////////////////////////////////////////////////////////

class Unique_v1 : private Noncopyable {};

class Unique_v2 : private Noncopyable
{
public:

    Unique_v2() = default;

//  Unique_v2([[maybe_unused]] const Unique_v2 & other) : Noncopyable(other) {} // error

    Unique_v2([[maybe_unused]] const Unique_v2 & other) : Noncopyable()
    {
        std::clog << "Unique_v2::Unique_v2\n";
    }

    auto & operator=([[maybe_unused]] const Unique_v2 & other)
    {
        std::clog << "Unique_v2::operator=\n";

    //  Noncopyable::operator=(other); // error

        return *this;
    }
};

class Unique_v3 : private boost::noncopyable {};

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Singleton::instance().test();

//  --------------------------------------------------------------

    [[maybe_unused]] Unique_v1 unique_v1_1;

//  [[maybe_unused]] Unique_v1 unique_v1_2 = unique_v1_1; // error

    [[maybe_unused]] Unique_v2 unique_v2_1;

    [[maybe_unused]] Unique_v2 unique_v2_2 = unique_v2_1;

    [[maybe_unused]] Unique_v3 unique_v3_1;

//  [[maybe_unused]] Unique_v3 unique_v3_2 = unique_v3_1; // error
}