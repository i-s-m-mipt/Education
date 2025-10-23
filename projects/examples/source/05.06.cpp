////////////////////////////////////////////////////////////////////

#include <print>

////////////////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>

////////////////////////////////////////////////////////////////////

class Noncopyable
{
public :

    Noncopyable            (Noncopyable const &) = delete;

//  ------------------------------------------------------

    Noncopyable & operator=(Noncopyable const &) = delete;

protected :

    Noncopyable() = default;
};

////////////////////////////////////////////////////////////////////

class Unique_v1 : private Noncopyable {};

////////////////////////////////////////////////////////////////////

class Unique_v2 : private Noncopyable
{
public :

    Unique_v2() = default;

//  ----------------------------------------------------------------

//  Unique_v2(Unique_v2 const & other) : Noncopyable(other) // error
//  {
//      std::print("Unique_v2::Unique_v2 (1)\n");
//  }

//  ----------------------------------------------------------------

    Unique_v2(Unique_v2 const &) : Noncopyable()
    {
        std::print("Unique_v2::Unique_v2 (2)\n");
    }

//  ----------------------------------------------------------------

    auto & operator=([[maybe_unused]] Unique_v2 const & other)
    {
        std::print("Unique_v2::operator=\n");

    //  Noncopyable::operator=(other); // error

        return *this;
    }
};

////////////////////////////////////////////////////////////////////

class Unique_v3 : private boost::noncopyable {};

////////////////////////////////////////////////////////////////////

template < typename U > void test()
{
    U unique_1;

    U unique_2 = unique_1;

      unique_2 = unique_1;
}

////////////////////////////////////////////////////////////////////

int main()
{
//  test < Unique_v1 > (); // error

    test < Unique_v2 > ();

//  test < Unique_v3 > (); // error
}

////////////////////////////////////////////////////////////////////