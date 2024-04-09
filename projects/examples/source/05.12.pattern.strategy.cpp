#include <iostream>

// =================================================================================================

class Computation 
{
public:

    virtual ~Computation() = default; // note: polymorphic base class

    virtual void compute() const = 0;

}; // class Computation

// =================================================================================================

class AVX : public Computation { public: void compute() const override { std::cout << "AVX" << std::endl; } };
class SSE : public Computation { public: void compute() const override { std::cout << "SSE" << std::endl; } };

// =================================================================================================

class Computer
{
public:

    explicit Computer(const Computation & computation) : m_computation(computation) {}

    void compute() const { m_computation.compute(); }

private:
    
    const Computation & m_computation;

}; // class Computer

// =================================================================================================

int main()
{
    Computer(AVX()).compute(); // note: instruction set for computations

    return 0;
}