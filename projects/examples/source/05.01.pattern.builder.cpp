#include <iostream>
#include <string>

// =================================================================================================

struct Computer
{
    const        std::string name;

    struct CPU { std::string name; } cpu;
    struct GPU { std::string name; } gpu;
    struct RAM { std::string name; } ram;
    
}; // struct Computer

// =================================================================================================

void print(const Computer & computer)
{
    std::cout << computer.name << " { " << computer.cpu.name << ", " <<
                                           computer.gpu.name << ", " <<
                                           computer.ram.name << " }" << std::endl;
}

// =================================================================================================

class Builder
{
public:

    explicit Builder(const std::string & name) : m_computer(new Computer { name }) {}

    virtual ~Builder() = default; // note: polymorphic base class

    [[nodiscard]] Computer * computer() const { return m_computer; }

    virtual void build_cpu() const = 0; // note: optional pure virtual function
    virtual void build_gpu() const = 0; // note: optional pure virtual function
    virtual void build_ram() const = 0; // note: optional pure virtual function

private:

    Computer * const m_computer; // note: consider smart pointer

}; // class Builder

// =================================================================================================

class Builder_Mobile : public Builder
{
public:

    explicit Builder_Mobile(const std::string & name) : Builder(name) {}

public:

    void build_cpu() const override { computer()->cpu.name = "MCPU"; }
    void build_gpu() const override { computer()->gpu.name = "MGPU"; }
    void build_ram() const override { computer()->ram.name = "MRAM"; }

}; // class Builder_Mobile : public Builder

// =================================================================================================

class Builder_Tablet : public Builder
{
public:

    explicit Builder_Tablet(const std::string & name) : Builder(name) {}

public:

    void build_cpu() const override { computer()->cpu.name = "TCPU"; }
    void build_gpu() const override { computer()->gpu.name = "TGPU"; }
    void build_ram() const override { computer()->ram.name = "TRAM"; }

}; // class Builder_Tablet : public Builder

// =================================================================================================

class Builder_Laptop : public Builder
{
public:

    explicit Builder_Laptop(const std::string & name) : Builder(name) {}

public:

    void build_cpu() const override { computer()->cpu.name = "LCPU"; }
    void build_gpu() const override { computer()->gpu.name = "LGPU"; }
    void build_ram() const override { computer()->ram.name = "LRAM"; }

}; // class Builder_Laptop : public Builder

// =================================================================================================

[[nodiscard]] inline const Computer * build(const Builder & builder) // note: consider member function
{
    builder.build_cpu();
    builder.build_gpu();
    builder.build_ram(); return builder.computer();
}

// =================================================================================================

int main()
{
    const auto mobile = build(Builder_Mobile("Mobile")); 

    print(*mobile); 
    
    delete mobile; // good: no memory leak

    return 0;
}