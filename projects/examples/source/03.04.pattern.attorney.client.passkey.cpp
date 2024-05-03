#include <iostream>

//  ================================================================================================

class Client
{
public:

    class Key
    {
    private:

        Key() {} // note: private constructor

        friend class User;

    }; // class Key

public:

    void f(Key) const { std::cout << "Client::f(Key)" << std::endl; }

private:

    void f(   ) const { std::cout << "Client::f     " << std::endl; }
    void g(   ) const { std::cout << "Client::g     " << std::endl; }
    void h(   ) const { std::cout << "Client::h     " << std::endl; }

    friend class Attorney;

}; // class Client

//  ================================================================================================

class Attorney 
{
private:

    static void call_f(const Client & client) { client.f(); }
    static void call_g(const Client & client) { client.g(); }

    friend class User;

}; // class Attorney 

//  ================================================================================================

class User // good: access to Client::f and Client::g only
{
public:

    void run(const Client & client) const
    {
        client.f({}); // note: PassKey idiom

        Attorney::call_f(client);
        Attorney::call_g(client);
    }

}; // class User

//  ================================================================================================

int main()
{
    User().run(Client());

    return 0;
}