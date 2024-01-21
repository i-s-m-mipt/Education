#include <iostream>
#include <string>

struct Computer
{
    const std::string name;

    struct CPU { std::string name; } cpu;
    struct GPU { std::string name; } gpu;
    struct RAM { std::string name; } ram;
    
}; // struct Computer

void print(const Computer & computer)
{
    std::cout << "Computer \"" << computer.name << "\" includes: " << std::endl;

    std::cout << "CPU: " << computer.cpu.name << std::endl;
    std::cout << "GPU: " << computer.gpu.name << std::endl;
    std::cout << "RAM: " << computer.ram.name << std::endl;
}

class Computer_Builder
{
public:

    explicit Computer_Builder(const std::string & name)
    {
        m_computer = new Computer{ .name = name }; // note: delete required
    }

    virtual ~Computer_Builder() = default;

public:

    [[nodiscard]] auto computer() const { return m_computer; }

public:

    virtual void build_CPU() const = 0; // note: optional pure virtual function
    virtual void build_GPU() const = 0; // note: optional pure virtual function
    virtual void build_RAM() const = 0; // note: optional pure virtual function

private:

    Computer * m_computer; // note: consider smart pointer

}; // class Computer_Builder

class Laptop_Builder : public Computer_Builder
{
public:

    explicit Laptop_Builder(const std::string & name) : Computer_Builder(name) {}

public:

    void build_CPU() const override { computer()->cpu.name = "AMD Ryzen 9 7945HX"; }
    void build_GPU() const override { computer()->gpu.name = "Nvidia GeForce RTX 4090M"; }
    void build_RAM() const override { computer()->ram.name = "Kingston Fury Impact DDR5"; }

}; // class Laptop_Builder : public Computer_Builder

class Desktop_Builder : public Computer_Builder
{
public:

    explicit Desktop_Builder(const std::string & name) : Computer_Builder(name) {}

public:

    void build_CPU() const override { computer()->cpu.name = "AMD Ryzen Threadripper Pro 7995WX"; }
    void build_GPU() const override { computer()->gpu.name = "Nvidia Quadro RTX A6000"; }
    void build_RAM() const override { computer()->ram.name = "Kingston Fury Renegade DDR5"; }

}; // class Desktop_Builder : public Computer_Builder

class Server_Builder : public Computer_Builder
{
public:

    explicit Server_Builder(const std::string & name) : Computer_Builder(name) {}

public:

    void build_CPU() const override { computer()->cpu.name = "AMD EPYC 9684"; }
    void build_GPU() const override { computer()->gpu.name = "Nvidia Hopper H100 Accelerator"; }
    void build_RAM() const override { computer()->ram.name = "Kingston Server Premier DDR5"; }

}; // class Server_Builder : public Computer_Builder

[[nodiscard]] auto build_computer(const Computer_Builder & builder) // note: consider member function
{
    builder.build_CPU();
    builder.build_GPU();
    builder.build_RAM();

    return builder.computer();
}

int main()
{
    auto computer = build_computer(Laptop_Builder("Laptop")); // good: laptop only here

    print(*computer);
    
    delete computer; // good: no memory leak

    return 0;
}