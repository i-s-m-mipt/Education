#include <iostream>

class Entity_v1{
public:
    virtual void test(){
        std::cout << "Entity_v1:: test()\n";
    }
};

class Entity_v2{
public:
    virtual void test(){
        std::cout << "Entity_v1:: test()\n";
    }
};

class Adapter_v1 : public Entity_v1{
public:
    virtual void test_v1() = 0;
    void test() override final { test_v1(); }
};

class Adapter_v2 : public Entity_v2{
public:
    virtual void test_v2() = 0;
    void test() override final { test_v2(); }
};

class Client : public Adapter_v1, public Adapter_v2{
public:
    void test_v1() override{
        std::cout << "Client call Entity_v1\n";
    }

    void test_v2() override{
        std::cout << "Client call Entity_v2\n";
    }
};

int main(){
    Client client;

    client.test_v1();
    client.test_v2();

    return 0;
}