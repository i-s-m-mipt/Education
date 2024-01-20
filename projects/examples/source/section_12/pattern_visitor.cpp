#include <iostream>
#include <memory>

class Visitor // note: evaluate computer performance based on runned tests 
{
public:

    double visit(const class Mobile * mobile) const;
    double visit(const class Tablet * tablet) const;
    double visit(const class Laptop * laptop) const;

}; // class Visitor

class Computer // note: single-responsibility and opened-closed principles
{
public:

    virtual ~Computer() noexcept = default; // note: polymorphic base class

    virtual double run_cpu_test() const = 0;
    virtual double run_gpu_test() const = 0;
    virtual double run_ram_test() const = 0;

    virtual double visit(Visitor * visitor) const = 0;

}; // class Computer 

class Mobile : public Computer 
{
public:

    double run_cpu_test() const override { return 1.0; }
    double run_gpu_test() const override { return 1.0; }
    double run_ram_test() const override { return 2.0; }

    double visit(Visitor * visitor) const override
    { 
        return visitor->visit(this); // note: second dispatch
    } 

}; // class Mobile : public Computer 

class Tablet : public Computer
{
public:

    double run_cpu_test() const override { return 2.0; }
    double run_gpu_test() const override { return 3.0; }
    double run_ram_test() const override { return 2.0; }

    double visit(Visitor * visitor) const override
    {
        return visitor->visit(this); // note: second dispatch
    }

}; // class Tablet : public Computer 

class Laptop : public Computer
{
public:

    double run_cpu_test() const override { return 4.0; }
    double run_gpu_test() const override { return 3.0; }
    double run_ram_test() const override { return 3.0; }

    double visit(Visitor * visitor) const override
    {
        return visitor->visit(this); // note: second dispatch
    }

}; // class Laptop : public Computer 

double Visitor::visit(const Mobile * mobile) const
{
    return (
        mobile->run_cpu_test() * 1.0 +
        mobile->run_gpu_test() * 2.0 +
        mobile->run_ram_test() * 4.0);
}

double Visitor::visit(const Tablet * tablet) const
{
    return (
        tablet->run_cpu_test() * 2.0 +
        tablet->run_gpu_test() * 4.0 +
        tablet->run_ram_test() * 1.0);
}

double Visitor::visit(const Laptop * laptop) const
{
    return (
        laptop->run_cpu_test() * 4.0 +
        laptop->run_gpu_test() * 1.0 +
        laptop->run_ram_test() * 2.0);
}

int main()
{
    auto mobile = std::make_shared < Mobile > ();
    auto tablet = std::make_shared < Tablet > ();
    auto laptop = std::make_shared < Laptop > ();

    Visitor visitor;

    std::cout << "mobile: " << mobile->visit(&visitor) << std::endl; // note: first dispatch
    std::cout << "tablet: " << tablet->visit(&visitor) << std::endl; // note: first dispatch
    std::cout << "laptop: " << laptop->visit(&visitor) << std::endl; // note: first dispatch

	return 0;
}