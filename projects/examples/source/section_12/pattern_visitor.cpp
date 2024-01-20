#include <iostream>
#include <memory>

class Mobile;
class Tablet;
class Laptop;

class Visitor
{
public:

    virtual ~Visitor() noexcept = default; // note: polymorphic base class

    [[nodiscard]] virtual double visit(const Mobile * mobile) const = 0;
    [[nodiscard]] virtual double visit(const Tablet * tablet) const = 0;
    [[nodiscard]] virtual double visit(const Laptop * laptop) const = 0;

}; // class Visitor

class Salesman : public Visitor // note: estimate price based on all tests 
{
public:

    double visit(const Mobile * mobile) const override;
    double visit(const Tablet * tablet) const override;
    double visit(const Laptop * laptop) const override;

}; // class Salesman : public Visitor

class Computer // note: single-responsibility and opened-closed principles
{
public:

    virtual ~Computer() noexcept = default; // note: polymorphic base class

    [[nodiscard]] virtual double run_cpu_test() const = 0;
    [[nodiscard]] virtual double run_gpu_test() const = 0;
    [[nodiscard]] virtual double run_ram_test() const = 0;

    [[nodiscard]] virtual double visit(Visitor * visitor) const = 0;

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

double Salesman::visit(const Mobile * mobile) const
{
    return (
        mobile->run_cpu_test() * 1.0 +
        mobile->run_gpu_test() * 2.0 +
        mobile->run_ram_test() * 4.0);
}

double Salesman::visit(const Tablet * tablet) const
{
    return (
        tablet->run_cpu_test() * 2.0 +
        tablet->run_gpu_test() * 4.0 +
        tablet->run_ram_test() * 1.0);
}

double Salesman::visit(const Laptop * laptop) const
{
    return (
        laptop->run_cpu_test() * 4.0 +
        laptop->run_gpu_test() * 1.0 +
        laptop->run_ram_test() * 2.0);
}

int main()
{
    std::shared_ptr < Computer > mobile = std::make_shared < Mobile > ();
    std::shared_ptr < Computer > tablet = std::make_shared < Tablet > ();
    std::shared_ptr < Computer > laptop = std::make_shared < Laptop > ();

    Salesman salesman;

    std::cout << mobile->visit(&salesman) << std::endl; // note: first dispatch
    std::cout << tablet->visit(&salesman) << std::endl; // note: first dispatch
    std::cout << laptop->visit(&salesman) << std::endl; // note: first dispatch

	return 0;
}