#include <iostream>

// =================================================================================================

class Computer
{
public:
    
    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual Computer * clone() const = 0; // note: virtual copy

    virtual void run() const = 0;

}; // class Computer

// =================================================================================================

class Mobile : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override { return new Mobile(*this); } 

    void run() const override { std::cout << "Mobile" << std::endl; };

}; // class Mobile : public Computer

// =================================================================================================

class Tablet : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override { return new Tablet(*this); } 

    void run() const override { std::cout << "Tablet" << std::endl; };

}; // class Tablet : public Computer

// =================================================================================================

class Laptop : public Computer
{
public:

    [[nodiscard]] Computer * clone() const override { return new Laptop(*this); } 

    void run() const override { std::cout << "Laptop" << std::endl; };

}; // class Laptop : public Computer

// =================================================================================================

class Factory // note: no factories hierarchy, static prototypes and virtual copy
{
public:

    [[nodiscard]] static Computer * create_mobile() { return mobile_prototype.clone(); }
    [[nodiscard]] static Computer * create_tablet() { return tablet_prototype.clone(); }
    [[nodiscard]] static Computer * create_laptop() { return laptop_prototype.clone(); }

private:

    static inline const Mobile mobile_prototype;
    static inline const Tablet tablet_prototype;
    static inline const Laptop laptop_prototype;

}; // class Factory

// =================================================================================================

int main()
{
    const Computer * const mobile = Factory::create_mobile(); 

    mobile->run(); 
    
    delete mobile; // good: no memory leak

    return 0;
}