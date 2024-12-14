#include <iostream>

////////////////////////////////////////////////////////////////////////

class Entity_v1
{
public:

    class Key_v1 { private: friend struct Client; Key_v1() = default; };

    class Key_v2 { private:                       Key_v2() = default; };

private:

    friend struct Client;

//  --------------------------------------------------------------------

    static void test(Key_v1) { std::cout << "Entity_v1::test (1)\n"; }
    static void test(Key_v2) { std::cout << "Entity_v1::test (2)\n"; }
};

////////////////////////////////////////////////////////////////////////

class Entity_v2
{
private:

    friend class Entity_v3;

//  --------------------------------------------------------------

    static void test_v1() { std::cout << "Entity_v2::test_v1\n"; }
    static void test_v2() { std::cout << "Entity_v2::test_v2\n"; } 
};

////////////////////////////////////////////////////////////////////////

class Entity_v3 
{
private:

    friend struct Client;

//  -----------------------------------------------

    static void test_v1() { Entity_v2::test_v1(); }

    static void test_v2() {}
};

////////////////////////////////////////////////////////////////////////

class Client
{
public:

    static void test_v1()
    {
        Entity_v1::test(Entity_v1::Key_v1());
    //  Entity_v1::test(Entity_v1::Key_v2()); // error
    }

    static void test_v2()
    {
        Entity_v3::test_v1();
        Entity_v3::test_v2();
    }
};

////////////////////////////////////////////////////////////////////////

int main()
{
    Client::test_v1();
    Client::test_v2();
}