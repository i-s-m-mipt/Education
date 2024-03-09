#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

class Visitor // good: provides additional functionality for other classes
{
public:

    virtual ~Visitor() noexcept = default; // note: polymorphic base class

    virtual void visit(const class Mobile * mobile) const = 0;
    virtual void visit(const class Tablet * tablet) const = 0;
    virtual void visit(const class Laptop * laptop) const = 0;

}; // class Visitor

class Computer // good: provides single-responsibility princile in compute
{
public:

    virtual ~Computer() noexcept = default; // note: polymorphic base class

    [[nodiscard]] virtual int run() const = 0; 

    virtual void visit_by(Visitor * visitor) const = 0;

}; // class Computer 

class Mobile : public Computer 
{
public:

    [[nodiscard]] int run() const override { return 0; };

    void visit_by(Visitor * visitor) const override
    { 
        return visitor->visit(this); // note: second dispatch
    }

}; // class Mobile : public Computer 

class Tablet : public Computer
{
public:

    [[nodiscard]] int run() const override { return 0; };

    void visit_by(Visitor * visitor) const override
    {
        return visitor->visit(this); // note: second dispatch
    }

}; // class Tablet : public Computer 

class Laptop : public Computer
{
public:

    [[nodiscard]] int run() const override { return 1; };

    void visit_by(Visitor * visitor) const override
    {
        return visitor->visit(this); // note: second dispatch
    }

}; // class Laptop : public Computer 

class Tester : public Visitor // note: provides simple tests for all computers
{
public:

    void visit(const Mobile * mobile) const override 
    { 
        if (mobile->run() != 0) throw std::runtime_error("invalid Mobile::run");
    }

    void visit(const Tablet * tablet) const override 
    {
        if (tablet->run() != 0) throw std::runtime_error("invalid Tablet::run");
    }

    void visit(const Laptop * laptop) const override 
    {
        if (laptop->run() != 0) throw std::runtime_error("invalid Laptop::run");
    }

}; // class Tester : public Visitor

int main()
{
    std::shared_ptr < Computer > computer_1 = std::make_shared < Mobile > ();
    std::shared_ptr < Computer > computer_2 = std::make_shared < Tablet > ();
    std::shared_ptr < Computer > computer_3 = std::make_shared < Laptop > ();

    Tester tester;

    try
    {
        computer_1->visit_by(&tester); // note: first dispatch
        computer_2->visit_by(&tester); // note: first dispatch
        computer_3->visit_by(&tester); // note: first dispatch
    }
    catch (const std::exception & exception)
    {
        std::cerr << "Tester error: " << exception.what() << '\n';
    }

	return 0;
}