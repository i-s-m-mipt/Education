#include <iostream>
#include <string>
#include <utility>

#include <boost/noncopyable.hpp>

//  ================================================================================================

class Computer : private boost::noncopyable // detail: header.hpp
{
public:

    explicit Computer(std::string name);

    Computer(Computer && other) : m_pimpl(other.m_pimpl)
    {
        other.m_pimpl = nullptr;
    }

    Computer & operator=(Computer && other)
    {
        m_pimpl = std::exchange(other.m_pimpl, nullptr); return *this;
    }

   ~Computer();

    void run() const;

private:

    class Implementation;

    const Implementation * m_pimpl; // support: std::experimental::propagate_const

}; // class Computer : private boost::noncopyable

//  ================================================================================================

class Computer::Implementation // detail: source.cpp
{
public:

    explicit Implementation(std::string name) : m_name(std::move(name)) {}

    void run() const { std::cout << m_name << std::endl; }

private:

    const std::string m_name;

}; // class Computer::Implementation

//  ================================================================================================

Computer:: Computer(std::string name) : m_pimpl(new const Implementation(std::move(name))) {}

Computer::~Computer() { delete m_pimpl; }

void Computer::run() const { m_pimpl->run(); }

//  ================================================================================================

int main()
{
    Computer("shape").run();

    return 0;
}