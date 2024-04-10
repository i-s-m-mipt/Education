#include <iostream>

// =================================================================================================

class Computer
{
public:
    
    virtual ~Computer() = default; // note: polymorphic base class

    [[nodiscard]] virtual const Computer * clone() const = 0; // note: virtual copy

    virtual void run() const = 0;

}; // class Computer

// =================================================================================================

class Mobile : public Computer
{
public:

    [[nodiscard]] const Computer * clone() const override { return new const Mobile(*this); } 

    void run() const override { std::cout << "Mobile" << std::endl; };

}; // class Mobile : public Computer

// =================================================================================================

class Tablet : public Computer
{
public:

    [[nodiscard]] const Computer * clone() const override { return new const Tablet(*this); } 

    void run() const override { std::cout << "Tablet" << std::endl; };

}; // class Tablet : public Computer

// =================================================================================================

class Laptop : public Computer
{
public:

    [[nodiscard]] const Computer * clone() const override { return new const Laptop(*this); } 

    void run() const override { std::cout << "Laptop" << std::endl; };

}; // class Laptop : public Computer

// =================================================================================================

class Factory // note: no factories hierarchy, static prototypes and virtual copy
{
public:

    [[nodiscard]] static const Computer * create_mobile() { return mobile_prototype.clone(); }
    [[nodiscard]] static const Computer * create_tablet() { return tablet_prototype.clone(); }
    [[nodiscard]] static const Computer * create_laptop() { return laptop_prototype.clone(); }

private:

    static inline const Mobile mobile_prototype; // note: consider new-delete instead of static
    static inline const Tablet tablet_prototype; // note: consider new-delete instead of static
    static inline const Laptop laptop_prototype; // note: consider new-delete instead of static

}; // class Factory

// =================================================================================================

int main()
{
    const Computer * const mobile = Factory::create_mobile(); 

    mobile->run(); 
    
    delete mobile; // good: no memory leak

    return 0;
}