#include <iostream>

//  ================================================================================================

class Entity_v1
{
    class Key_v1 { Key_v1() = default; friend struct Client; };

    class Key_v2 { Key_v2() = default; };

//  ------------------------------------------------------------------------------------------------

    friend struct Client;

//  ------------------------------------------------------------------------------------------------

    static void test(Key_v1) { std::clog << "Entity_v1::test (1)\n"; }
    static void test(Key_v2) { std::clog << "Entity_v1::test (2)\n"; }
};

//  ================================================================================================

class Entity_v2
{
    friend class Entity_v3;

//  ------------------------------------------------------------------------------------------------

    static void test_v1() { std::clog << "Entity_v2::test_v1\n"; }
    static void test_v2() { std::clog << "Entity_v2::test_v2\n"; }
};

//  ================================================================================================

class Entity_v3 
{
    friend struct Client;

//  ------------------------------------------------------------------------------------------------

    static void test_v1() { Entity_v2::test_v1(); }

    static void test_v2() {}
};

//  ================================================================================================

struct Client
{
    static void test_v1()
    {
        Entity_v1::test(Entity_v1::Key_v1());
//      Entity_v1::test(Entity_v1::Key_v2()); // error
    }

    static void test_v2()
    {
        Entity_v3::test_v1();
        Entity_v3::test_v2();
    }
};

//  ================================================================================================

int main()
{
    Client::test_v1();
    Client::test_v2();
}