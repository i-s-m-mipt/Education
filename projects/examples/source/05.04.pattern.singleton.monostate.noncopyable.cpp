#include <cassert>
#include <iostream>

#include <boost/noncopyable.hpp>

//  ================================================================================================

class Singleton
{
private:

    Singleton() = default;

public:

    Singleton            (const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;

//  ------------------------------------------------------------------------------------------------

    [[nodiscard]] static auto & get_instance() 
    { 
        static Singleton instance; 
        
        return instance; 
    }

//  ------------------------------------------------------------------------------------------------

    void test() const
    { 
        std::clog << "Singleton::test\n"; 
    }
};

//  ================================================================================================

class Monostate
{
public:

    [[nodiscard]] auto data() const
    { 
        return s_data; 
    }

    void set_data(int data) 
    { 
        s_data = data < 0 ? 0 : data; 
    }

private:

    static inline auto s_data = 0;   
};

//  ================================================================================================

class Noncopyable
{
protected:

    Noncopyable() = default;

    Noncopyable            (const Noncopyable &) = delete;
    Noncopyable & operator=(const Noncopyable &) = delete;

   ~Noncopyable() = default;
};

//  ================================================================================================

struct Unique_v1 : private        Noncopyable {};
struct Unique_v2 : private boost::noncopyable {};

//  ================================================================================================

int main()
{
    Singleton::get_instance().test();

//  ------------------------------------------------------------------------------------------------

    Monostate monostate_1; monostate_1.set_data(1);
    Monostate monostate_2; 

    assert
    (
        monostate_1.data() == 
        monostate_2.data()
    );

//  ------------------------------------------------------------------------------------------------

    [[maybe_unused]] Unique_v1 unique_v1_1;
//  [[maybe_unused]] Unique_v1 unique_v1_2 = unique_v1_1; // error

    [[maybe_unused]] Unique_v2 unique_v2_1;
//  [[maybe_unused]] Unique_v2 unique_v2_2 = unique_v2_1; // error
}