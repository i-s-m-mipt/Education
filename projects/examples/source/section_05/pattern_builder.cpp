#include <iostream>
#include <string>

struct Computer
{
    const std::string name;

    struct CPU { std::string name; } cpu;
    struct GPU { std::string name; } gpu;
    struct RAM { std::string name; } ram;
    
}; // struct Computer

class Builder
{
public:

    explicit Builder(const std::string & name)
    {
        m_computer = new Computer{ .name = name }; // note: delete required
    }

    virtual ~Builder() = default; // note: polymorphic base class

    [[nodiscard]] auto computer() const { return m_computer; }

    virtual void build_cpu() const = 0; // note: optional pure virtual function
    virtual void build_gpu() const = 0; // note: optional pure virtual function
    virtual void build_ram() const = 0; // note: optional pure virtual function

private:

    Computer * m_computer; // note: consider smart pointer

}; // class Builder

class Builder_Mobile : public Builder
{
public:

    explicit Builder_Mobile(const std::string & name) : Builder(name) {}

public:

    void build_cpu() const override { computer()->cpu.name = "Mobile CPU"; }
    void build_gpu() const override { computer()->gpu.name = "Mobile GPU"; }
    void build_ram() const override { computer()->ram.name = "Mobile RAM"; }

}; // class Builder_Mobile : public Builder

class Builder_Tablet : public Builder
{
public:

    explicit Builder_Tablet(const std::string & name) : Builder(name) {}

public:

    void build_cpu() const override { computer()->cpu.name = "Tablet CPU"; }
    void build_gpu() const override { computer()->gpu.name = "Tablet GPU"; }
    void build_ram() const override { computer()->ram.name = "Tablet RAM"; }

}; // class Builder_Tablet : public Builder

class Builder_Laptop : public Builder
{
public:

    explicit Builder_Laptop(const std::string & name) : Builder(name) {}

public:

    void build_cpu() const override { computer()->cpu.name = "Laptop CPU"; }
    void build_gpu() const override { computer()->gpu.name = "Laptop GPU"; }
    void build_ram() const override { computer()->ram.name = "Laptop RAM"; }

}; // class Builder_Laptop : public Builder

[[nodiscard]] auto build(const Builder & builder) // note: consider member function
{
    builder.build_cpu();
    builder.build_gpu();
    builder.build_ram();

    return builder.computer();
}

int main()
{
    delete build(Builder_Mobile("Mobile")); // good: no memory leak
    delete build(Builder_Tablet("Tablet")); // good: no memory leak
    delete build(Builder_Laptop("Laptop")); // good: no memory leak

    return 0;
}