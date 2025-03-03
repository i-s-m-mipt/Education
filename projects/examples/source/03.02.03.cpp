#include <iostream>

///////////////////////////////////////////////////////////////////////

class Entity
{
public:

    class Key_v1 { private: friend class Client; Key_v1() = default; };

    class Key_v2 { private:                      Key_v2() = default; };

private:

    friend class Client;

//  -------------------------------------------------------------------

    static void test(Key_v1) { std::cout << "Entity::test (1)\n"; }
    
    static void test(Key_v2) { std::cout << "Entity::test (2)\n"; }
};

///////////////////////////////////////////////////////////////////////

class Client
{
public:

    static void test()
    {
        Entity::test(Entity::Key_v1());

    //  Entity::test(Entity::Key_v2()); // error
    }
};

///////////////////////////////////////////////////////////////////////

int main()
{
    Client::test();
}