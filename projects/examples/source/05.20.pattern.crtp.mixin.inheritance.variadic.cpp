#include <iostream>

// =================================================================================================

class Color_v1 { public: explicit Color_v1(char) {}; };
class Label_v1 { public: explicit Label_v1(char) {}; };

// =================================================================================================

template < typename ... Bases > class Point_v1 : public Bases... // note: modern mixin
{
public:

    template < typename ... Ts > explicit Point_v1(double x, double y, Ts ... args) : Bases(args)..., m_x(x), m_y(y)
    {
        std::cout << sizeof...(Bases) << std::endl;
    }

    template < typename V > void visit(V visitor)
    {
        visitor(static_cast < Bases & > (*this)...);
    }

private:

    double m_x, m_y;

}; // class Point_v1 : public Bases...

// =================================================================================================

template < typename T > class Color_v2 {}; // note: consider protected destructor and EBO
template < typename T > class Label_v2 {}; // note: consider protected destructor and EBO

// =================================================================================================

template < template < typename E > typename ... Bases > class Point_v2 :
    public Bases < Point_v2 < Bases ... > > ... 
{
public:

    explicit Point_v2(double x, double y) : Bases < Point_v2 > ()..., m_x(x), m_y(y)
    {
        std::cout << sizeof...(Bases) << std::endl;
    }

    template < typename V > void visit(V visitor)
    {
        visitor(static_cast < Bases < Point_v2 > & > (*this)...);
    }

private:

    double m_x, m_y;

}; // class Point_v2 : public Bases < Point_v2 < Bases ... > > ... 

// =================================================================================================

int main()
{
    const Point_v1 < Color_v1, Label_v1 > point_v1_1(1.0, 1.0, 'a', 'b');
    const Point_v1 < Color_v1           > point_v1_2(2.0, 2.0, 'a');
    const Point_v1 <                    > point_v1_3(3.0, 3.0);

    const Point_v2 < Color_v2, Label_v2 > point_v2_1(1.0, 1.0);
    const Point_v2 < Color_v2           > point_v2_2(2.0, 2.0);
    const Point_v2 <                    > point_v2_3(3.0, 3.0);

    return 0;
}