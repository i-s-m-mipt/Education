#include <iostream>

class Drawing_API 
{
public:

    virtual ~Drawing_API() = default;

    virtual void draw() const = 0;

}; // class Drawing_API 

class Drawing_API_v1 : public Drawing_API 
{
public:

    void draw() const override { std::cout << "drawing API v1" << std::endl; }

}; // class Drawing_API_v1 : public Drawing_API 

class Drawing_API_v2 : public Drawing_API 
{
public:

    void draw() const override { std::cout << "drawing API v2" << std::endl; }

}; // class Drawing_API_v2 : public Drawing_API 

class Shape 
{
public:

    explicit Shape(const Drawing_API & drawing_API) : m_drawing_API(drawing_API) {}

    virtual void draw() const = 0;

protected:

    const Drawing_API & m_drawing_API;

}; // class Shape 

class Triangle : public Shape 
{
public:

    explicit Triangle(const Drawing_API & drawing_API) : Shape(drawing_API) {}

    void draw() const override { m_drawing_API.draw(); }

}; // class Triangle : public Shape 

int main() 
{
    Triangle(Drawing_API_v1()).draw();
    Triangle(Drawing_API_v2()).draw();

    return 0;
}