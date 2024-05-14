#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

//  ================================================================================================

class Visitor
{
public:

    virtual ~Visitor() noexcept = default; 

    virtual void visit(const class Mobile * mobile) const = 0;
    virtual void visit(const class Tablet * tablet) const = 0;
    virtual void visit(const class Laptop * laptop) const = 0;

}; // class Visitor

//  ================================================================================================

class Computer
{
public:

    virtual ~Computer() noexcept = default; 

    [[nodiscard]] virtual int run() const noexcept = 0; 

    virtual void visit_by(Visitor * visitor) const = 0;

}; // class Computer 

//  ================================================================================================

class Mobile : public Computer 
{
public:

    [[nodiscard]] int run() const noexcept override { return 42; };

    void visit_by(Visitor * visitor) const override
    { 
        return visitor->visit(this);
    }

}; // class Mobile : public Computer 

//  ================================================================================================

class Tablet : public Computer
{
public:

    [[nodiscard]] int run() const noexcept override { return 42; };

    void visit_by(Visitor * visitor) const override
    {
        return visitor->visit(this);
    }

}; // class Tablet : public Computer 

//  ================================================================================================

class Laptop : public Computer
{
public:

    [[nodiscard]] int run() const noexcept override { return 43; };

    void visit_by(Visitor * visitor) const override
    {
        return visitor->visit(this);
    }

}; // class Laptop : public Computer 

//  ================================================================================================

class Tester : public Visitor
{
public:

    void visit(const Mobile * mobile) const override 
    { 
        if (mobile->run() != 42) throw std::runtime_error("invalid Mobile");
    }

    void visit(const Tablet * tablet) const override 
    {
        if (tablet->run() != 42) throw std::runtime_error("invalid Tablet");
    }

    void visit(const Laptop * laptop) const override 
    {
        if (laptop->run() != 42) throw std::runtime_error("invalid Laptop");
    }

}; // class Tester : public Visitor

//  ================================================================================================

int main()
{
    const std::shared_ptr < const Computer > computer_1 = std::make_shared < const Mobile > ();
    const std::shared_ptr < const Computer > computer_2 = std::make_shared < const Tablet > ();
    const std::shared_ptr < const Computer > computer_3 = std::make_shared < const Laptop > ();

    Tester tester;

    try
    {
        computer_1->visit_by(&tester);
        computer_2->visit_by(&tester);
        computer_3->visit_by(&tester);
    }
    catch (const std::exception & exception)
    {
        std::cerr << "Tester error: " << exception.what() << '\n';
    }

	return 0;
}