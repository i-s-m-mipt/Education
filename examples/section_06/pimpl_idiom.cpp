#include <iostream>
#include <string>

class Shape // note: placed in the header file, consider also forward declarations
{
public:

    explicit Shape(std::string name); // note: definition in source file

    Shape            (const Shape &) = delete;
    Shape & operator=(const Shape &) = delete;

    Shape(Shape && other) noexcept : m_pimpl(other.m_pimpl) // note: ignore noexcept here
    {
        other.m_pimpl = nullptr;
    }

    Shape & operator=(Shape && other) noexcept // note: ignore noexcept here
    {
        m_pimpl = other.m_pimpl; other.m_pimpl = nullptr;
    }

    ~Shape();

    void draw() const; // note: call forwarded to implementation, no inline abilities

private:

    class Implementation; // note: implemetation hidden in the source file

    Implementation * m_pimpl; // note: use std::experimental::propagate_const

}; // class Shape

class Shape::Implementation // note: placed in the source file
{
public:

    explicit Implementation(std::string name) : m_name(std::move(name)) {}

    void draw() const { std::cout << m_name << std::endl; }

private:

    std::string m_name;

}; // class Shape::Implementation

Shape::Shape(std::string name) : m_pimpl(new Implementation(std::move(name))) {}

Shape::~Shape() { delete m_pimpl; }

void Shape::draw() const { m_pimpl->draw(); }

int main()
{
    Shape("shape").draw();

    return 0;
}