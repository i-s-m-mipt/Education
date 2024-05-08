#include <iostream>

//  ================================================================================================

class Computation 
{
public:

    virtual ~Computation() = default; 

    virtual void compute() const = 0;

}; // class Computation

//  ================================================================================================

class AVX : public Computation { public: void compute() const override; };
class SSE : public Computation { public: void compute() const override; };

//  ================================================================================================

void AVX::compute() const { std::cout << "AVX" << std::endl; }
void SSE::compute() const { std::cout << "SSE" << std::endl; }

//  ================================================================================================

class Computer
{
public:

    explicit Computer(const Computation & computation) : m_computation(computation) {}

    void compute() const { m_computation.compute(); }

private:
    
    const Computation & m_computation;

}; // class Computer

//  ================================================================================================

int main()
{
    Computer(AVX()).compute();

    return 0;
}