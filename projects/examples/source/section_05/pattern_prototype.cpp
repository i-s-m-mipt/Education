#include <iostream>

class Computer
{
public:
    
    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual Computer * clone() const = 0; // note: virtual copy

    virtual void run() const = 0;

}; // class Computer

class Mobile : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Mobile(*this); // note: delete required
    } 

    void run() const override { std::cout << "Mobile" << std::endl; };

}; // class Mobile : public Computer

class Tablet : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Tablet(*this); // note: delete required
    } 

    void run() const override { std::cout << "Tablet" << std::endl; };

}; // class Tablet : public Computer

class Laptop : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override 
    { 
        return new Laptop(*this); // note: delete required
    } 

    void run() const override { std::cout << "Laptop" << std::endl; };

}; // class Laptop : public Computer

class Factory // note: no factories hierarchy, static prototypes and virtual copy
{
public:

    [[nodiscard]] static auto create_mobile() { return mobile_prototype.clone(); }
    [[nodiscard]] static auto create_tablet() { return tablet_prototype.clone(); }
    [[nodiscard]] static auto create_laptop() { return laptop_prototype.clone(); }

private:

    static inline const Mobile mobile_prototype;
    static inline const Tablet tablet_prototype;
    static inline const Laptop laptop_prototype;

}; // struct Factory

int main()
{
    delete Factory::create_mobile();
    delete Factory::create_tablet();
    delete Factory::create_laptop();

    return 0;
}