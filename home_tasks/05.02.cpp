#include <iostream>

class Entity {
public:
    virtual void perform() const = 0;
    virtual ~Entity() = default;
};

template <typename T>
class Decorator : public Entity, public virtual T {
public:
    using T::T;
    
    void perform() const override {
        T::perform();
    }
};

class MyEntity : public virtual Entity {
public:
    void perform() const override {
        std::cout << "MyEntity operation\n";
    }
};

int main() {
    Decorator<MyEntity> decorated;
    decorated.perform();
    return 0;
}