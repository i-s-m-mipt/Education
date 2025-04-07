///////////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////////

class Entity
{
private :

    friend class Attorney;

//  -----------------------------------------------------------

    static void test_v1() { std::cout << "Entity::test_v1\n"; }

    static void test_v2() { std::cout << "Entity::test_v2\n"; }
};

///////////////////////////////////////////////////////////////

class Attorney 
{
private :

    friend class Client;

//  ---------------------------------------

    static void test_v1() 
    { 
        std::cout << "Attorney::test_v1\n";

    //  -----------------------------------

        Entity::test_v1();
    }

//  ---------------------------------------

    static void test_v2() 
    { 
        std::cout << "Attorney::test_v2\n";
    }
};

///////////////////////////////////////////////////////////////

class Client
{
public :

    static void test()
    {
        Attorney::test_v1();

        Attorney::test_v2();
    }
};

///////////////////////////////////////////////////////////////

int main()
{
    Client::test();
}

///////////////////////////////////////////////////////////////