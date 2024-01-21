#include <iostream>
#include <string>

class Shape 
{
public:

    virtual ~Shape() = default;

public:

    [[nodiscard]] virtual std::string description() const = 0;

}; // class Shape 

class Polygon : public Shape 
{
public:

    [[nodiscard]] std::string description() const override
    { 
        return "Polygon"; 
    }

}; // class Polygon

class Decorated_Shape : public Shape // note: abstract decorator
{
public:

    explicit Decorated_Shape(Shape * shape): m_shape(shape)
    {
        if (!m_shape) // good: verify if nullptr
        {
            std::cout << "invalid shape" << std::endl;
        }
    }

public:

    [[nodiscard]] std::string description() const override
    { 
        return m_shape->description(); 
    }

protected:

    Shape * m_shape;

}; // class Decorated_Shape : public Shape 

class Colored_Shape : public Decorated_Shape // note: concrete decorator
{
public:

    explicit Colored_Shape(Shape * shape) : Decorated_Shape(shape) {}

public:

    [[nodiscard]] std::string description() const override
    { 
        return m_shape->description() + " with Color"; 
    }

}; // class Colored_Shape : public Decorated_Shape

int main()
{
    Shape * shape_1 = new Polygon();

    std::cout << shape_1->description() << std::endl;

    Shape * shape_2 = new Colored_Shape(shape_1);

    std::cout << shape_2->description() << std::endl;

    delete shape_1; // good: no memory leak
    delete shape_2; // good: no memory leak

    return 0;
}