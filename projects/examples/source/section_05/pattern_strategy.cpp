#include <iostream>

class Computation 
{
public:

    virtual ~Computation() = default; // note: polymorphic base class

    virtual void compute() const = 0;

}; // class Computation

struct AVX : public Computation { void compute() const override { std::cout << "AVX" << std::endl; } };
struct SSE : public Computation { void compute() const override { std::cout << "SSE" << std::endl; } };

class Computer
{
public:

    explicit Computer(Computation * computation) : m_computation(computation) 
    {
        if (!m_computation) std::cout << "invalid computation" << std::endl;
    }

    ~Computer() { delete m_computation; } // good: no memory leak

    void compute() const { m_computation->compute(); }

private:
    
    Computation * m_computation;

}; // class Computer

int main()
{
    Computer(new AVX).compute(); // note: instruction set for computations

    return 0;
}