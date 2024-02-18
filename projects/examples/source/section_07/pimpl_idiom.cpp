#include <iostream>
#include <string>

#include <boost/noncopyable.hpp>

class Computer : private boost::noncopyable // note: placed in the header file
{
public:

    explicit Computer(std::string name); // note: definition in source file

    Computer(Computer && other) noexcept : m_pimpl(other.m_pimpl) // note: ignore noexcept here
    {
        other.m_pimpl = nullptr;
    }

    Computer & operator=(Computer && other) noexcept // note: ignore noexcept here
    {
        m_pimpl = other.m_pimpl; other.m_pimpl = nullptr; return *this;
    }

    ~Computer();

    void run() const; // note: call forwarded to implementation, no inline abilities

private:

    class Implementation; // note: implemetation hidden in the source file

    Implementation * m_pimpl; // note: use std::experimental::propagate_const

}; // class Computer : private boost::noncopyable

class Computer::Implementation // note: placed in the source file
{
public:

    explicit Implementation(std::string name) : m_name(std::move(name)) {}

    void run() const { std::cout << m_name << std::endl; }

private:

    std::string m_name;

}; // class Computer::Implementation

Computer::Computer(std::string name) : m_pimpl(new Implementation(std::move(name))) {}

Computer::~Computer() { delete m_pimpl; }

void Computer::run() const { m_pimpl->run(); }

int main()
{
    Computer("shape").run();

    return 0;
}