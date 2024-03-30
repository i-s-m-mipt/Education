#include <iostream>

// =================================================================================================

class Color_v1 { public: explicit Color_v1(char) {}; };
class Label_v1 { public: explicit Label_v1(char) {}; };

// =================================================================================================

template < typename ... Bases > 
class Point_v1 : public Bases... // note: modern mixin
{
public:

    template < typename ... Types > 
    explicit Point_v1(double x, double y, Types ... args) : Bases(args)..., m_x(x), m_y(y)
    {
        std::cout << sizeof...(Bases) << std::endl;
    }

private:

    double m_x;
    double m_y;

}; // class Point_v1 : public Bases...

// =================================================================================================

template < typename T > class Color_v2 {}; // note: consider protected destructor and EBO
template < typename T > class Label_v2 {}; // note: consider protected destructor and EBO

// =================================================================================================

template < template < typename > typename ... Bases > // note: template template parameters
class Point_v2 : public Bases < Point_v2 < Bases ... > > ... 
{
public:

    explicit Point_v2(double x, double y) : Bases < Point_v2 > ()..., m_x(x), m_y(y)
    {
        std::cout << sizeof...(Bases) << std::endl;
    }

private:

    double m_x;
    double m_y;

}; // class Point_v2 : public Bases < Point_v2 < Bases ... > > ... 

// =================================================================================================

int main()
{
    const Point_v1 < Color_v1, Label_v1 > p1_v1(1.0, 1.0, 'a', 'b');
    const Point_v1 < Color_v1           > p2_v1(2.0, 2.0, 'a');
    const Point_v1 <                    > p3_v1(3.0, 3.0);

    const Point_v2 < Color_v2, Label_v2 > p1_v2(1.0, 1.0);
    const Point_v2 < Color_v2           > p2_v2(2.0, 2.0);
    const Point_v2 <                    > p3_v2(3.0, 3.0);

    return 0;
}