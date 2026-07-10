////////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Programming with Algorithms

////////////////////////////////////////////////////////////////////////////////////////////////////

// content : Variants

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <print>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/mp11.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > struct Deque {};

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using front = boost::mp11::mp_front < D > ;

////////////////////////////////////////////////////////////////////////////////////////////////////

template
<
    typename T1, typename T2
>
using Comparator = std::integral_constant < bool, sizeof(T1) < sizeof(T2) > ;

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using max_type = boost::mp11::mp_max_element < D, Comparator > ;

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T > constexpr auto index_v = boost::mp11::mp_find < D, T > ::value;

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > class Storage
{
protected :

    Storage() = default;

//  ---------------------------------------------------------------------------------------------

    template < typename T > auto get_type()
    {
        return reinterpret_cast < T * > (std::begin(m_array));
    }

//  ---------------------------------------------------------------------------------------------

    alignas(Ts...) std::array < std::byte, sizeof(max_type < Deque < Ts ... > > ) > m_array = {};

    std::size_t m_index = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T, typename ... Ts > class Handler
{
public :

    Handler(T x)
    {
        std::construct_at(derived().template get_type < T > (), std::move(x));

        derived().m_index = s_index;
    }

//  ------------------------------------------------------------------------------

    auto & operator=(T x)
    {
        if (derived().m_index == s_index)
        {
            *derived().template get_type < T > () = std::move(x);
        }
        else
        {
            derived().destroy();

            std::construct_at(derived().template get_type < T > (), std::move(x));

            derived().m_index = s_index;
        }

        return derived();
    }

protected :

    Handler() = default;

//  ------------------------------------------------------------------------------

    void destroy()
    {
        if (derived().m_index == s_index)
        {
            std::destroy_at(derived().template get_type < T > ());
        }
    }

//  ------------------------------------------------------------------------------

    constexpr static auto s_index = index_v < Deque < Ts ... > , T > + 1;

private :

    auto & derived()
    {
        return *static_cast < D * > (this);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template
<
    typename ... Ts
>
class Variant : private Storage < Ts ... > , private Handler < Variant < Ts ... > , Ts, Ts ... > ...
{
public :

    Variant()
    {
        *this = front < Deque < Ts ... > > ();
    }

//  -------------------------------------------------------------------------------------------

    Variant(Variant const & other) : Handler < Variant < Ts ... > , Ts, Ts ... > ::Handler()...
    {
        this->m_array = other.m_array;

        this->m_index = other.m_index;
    }

//  -------------------------------------------------------------------------------------------

    Variant(Variant && other) : Variant()
    {
        swap(other);
    }

//  -------------------------------------------------------------------------------------------

   ~Variant()
    {
        destroy();
    }

//  -------------------------------------------------------------------------------------------

    auto & operator=(Variant other)
    {
        swap(other);

		return *this;
    }

//  -------------------------------------------------------------------------------------------

    using Handler < Variant < Ts ... > , Ts, Ts ... > ::Handler  ...;

    using Handler < Variant < Ts ... > , Ts, Ts ... > ::operator=...;

//  -------------------------------------------------------------------------------------------

    void swap(Variant & other)
	{
        std::swap(this->m_array, other.m_array);

		std::swap(this->m_index, other.m_index);
	}

//  -------------------------------------------------------------------------------------------

    template < typename T > auto holds_alternative() const
    {
        return this->m_index == Handler < Variant < Ts ... > , T, Ts ... > ::s_index;
    }

//  -------------------------------------------------------------------------------------------

    template < typename T > auto get()
    {
        return *this->template get_type < T > ();
    }

//  -------------------------------------------------------------------------------------------

    template < typename V > auto visit(V && visitor)
    {
        return visit_implementation(std::forward < V > (visitor), Deque < Ts ... > ());
    }

private :

    template < typename D, typename U, typename ... Us > friend class Handler;

//  -------------------------------------------------------------------------------------------

    void destroy()
    {
        (Handler < Variant < Ts ... > , Ts, Ts ... > ::destroy(), ...);

        this->m_index = 0;
    }

//  -------------------------------------------------------------------------------------------

    template
    <
        typename V, typename U, typename ... Us
    >
    auto visit_implementation(V && visitor, Deque < U, Us ... > )
    {
        if (this->template holds_alternative < U > ())
        {
            return visitor(this->template get < U > ());
        }

        if constexpr (sizeof...(Us) > 0)
        {
            return visit_implementation(std::forward < V > (visitor), Deque < Us ... > ());
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class Visitor
{
public :

    static void operator()(int x)
    {
        std::print("Visitor::operator() : x = {}\n", x);
    }

//  --------------------------------------------------------------

    static void operator()(double x)
    {
        std::print("Visitor::operator() : x = {}\n", x);
    }

//  --------------------------------------------------------------

    static void operator()(std::string const & string)
    {
        std::print("Visitor::operator() : string = {}\n", string);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(int) {}

//  ------------------------------------

   ~Entity()
    {
		std::print("Entity::~Entity\n");
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Variant < int, double, std::string > variant_1;

    Variant < int, double, std::string > variant_2 = 2;

    Variant < int, double, std::string > variant_3 = variant_2;

    Variant < int, double, std::string > variant_4 = std::move(variant_3);

//  ----------------------------------------------------------------------

    variant_3 = variant_2;

    variant_4 = std::move(variant_3);

    variant_1 = 1;

//  ----------------------------------------------------------------------

    assert(variant_1.holds_alternative < int > ());

//  ----------------------------------------------------------------------

    assert(variant_1.get < int > () == 1);

//  ----------------------------------------------------------------------

    variant_1.visit(Visitor());

//  ----------------------------------------------------------------------

//	std::variant < Entity, int > variant_5; // error

//  ----------------------------------------------------------------------

    std::variant < std::monostate, Entity, int > variant_6;
}

////////////////////////////////////////////////////////////////////////////////////////////////////