#include <iostream>

struct CPU
{
    void make_slow() const { std::cout << "CPU is slow" << std::endl; }
    void make_fast() const { std::cout << "CPU is fast" << std::endl; }

}; // struct CPU

struct GPU
{
    void make_slow() const { std::cout << "GPU is slow" << std::endl; }
    void make_fast() const { std::cout << "GPU is fast" << std::endl; }

}; // struct GPU 

struct RAM
{
    void make_slow() const { std::cout << "RAM is slow" << std::endl; }
    void make_fast() const { std::cout << "RAM is fast" << std::endl; }

}; // struct RAM 

class Computer 
{
public:

    void make_slow() const
    {
        m_cpu.make_slow();
        m_gpu.make_slow();
        m_ram.make_slow();
    }

    void make_fast() const
    {
        m_cpu.make_fast();
        m_gpu.make_fast();
        m_ram.make_fast();
    }

private:

    CPU m_cpu;
    GPU m_gpu;
    RAM m_ram;

}; // class Computer 

int main() 
{
    Computer computer;

    computer.make_fast();
    computer.make_slow();

    return 0;
}