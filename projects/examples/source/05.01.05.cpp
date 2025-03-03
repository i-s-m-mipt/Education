#include <iostream>

//////////////////////////////////////////////////////

class Singleton
{
public:

    Singleton            (const Singleton &) = delete;

    Singleton & operator=(const Singleton &) = delete;

//  --------------------------------------------------

    void test() const
    { 
        std::cout << "Singleton::test\n";
    }

//  --------------------------------------------------

    static auto & get() 
    { 
        static Singleton singleton;
        
        return singleton;
    }

private:

    Singleton() = default;
};

//////////////////////////////////////////////////////

int main()
{
    Singleton::get().test();
}