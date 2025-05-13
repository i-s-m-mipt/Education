/////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <bit>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > struct Deque {};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Size {};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > struct Size < Deque < Ts ... > >
{
    constexpr static auto value = sizeof...(Ts);
};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > constexpr auto size_v = Size < D > ::value;

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > constexpr auto is_empty_v = size_v < D > == 0;

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Front {};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > struct Front < Deque < T, Ts ... > > 
{ 
    using type = T;
};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using front = typename Front < D > ::type;

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Pop_Front {};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > struct Pop_Front < Deque < T, Ts ... > >
{
    using type = Deque < Ts ... > ;
};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using pop_front = typename Pop_Front < D > ::type;

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, bool C = is_empty_v < D > > class Max_Type {};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Max_Type < D, false >
{
private :

    using current_t = front < D > ;

    using max_t = typename Max_Type < pop_front < D > > ::type;

public :

    using type = std::conditional_t < sizeof(current_t) >= sizeof(max_t), current_t, max_t > ;
};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Max_Type < D, true > 
{ 
public : 
        
    using type = char;
};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using max_type = typename Max_Type < D > ::type;

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T, std::size_t I = 0, bool C = is_empty_v < D > > class Index {};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T, std::size_t I > class Index < D, T, I, false > 
:
    public std::conditional_t 
    < 
        std::is_same_v < front < D > , T > ,

        std::integral_constant < std::size_t, I > , 

        Index < pop_front < D > , T, I + 1 > 
    > 
{};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T, std::size_t I > class Index < D, T, I, true > {};

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T > constexpr auto index_v = Index < D, T > ::value;

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > class Storage
{
protected :

    Storage() = default;

   ~Storage() = default;

//  ---------------------------------------------------------------------------------------------

    template < typename T > auto get_type() const
    {
        return std::bit_cast < T * > (std::begin(m_array));
    }

//  ---------------------------------------------------------------------------------------------

    alignas(Ts...) std::array < std::byte, sizeof(max_type < Deque < Ts ... > > ) > m_array = {};

    std::size_t m_index = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////

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

   ~Handler() = default;

//  ------------------------------------------------------------------------------

    void destroy()
    {
        if (derived().m_index == s_index) 
        {
            derived().template get_type < T > ()->~T();
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

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > class Variant 
: 
    private Storage           < Ts ... > , 

    private Handler < Variant < Ts ... > , Ts, Ts ... > ...
{
public :

    Variant() 
    { 
        *this = front < Deque < Ts ... > > ();
    }

//  -------------------------------------------------------------------------------------------

    Variant(Variant const & other) : Handler < Variant < Ts ... > , Ts, Ts ... > ::Handler()...
    {
        auto lambda = [this](auto && x){ *this = x; };

        other.visit(lambda);
    }

//  -------------------------------------------------------------------------------------------

    Variant(Variant && other)
    {
        auto lambda = [this](auto && x){ *this = std::move(x); };

        other.visit(lambda);
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

    void swap(Variant & other)
	{
        std::swap(this->m_array, other.m_array);

		std::swap(this->m_index, other.m_index);
	}

//  -------------------------------------------------------------------------------------------

    using Handler < Variant < Ts ... > , Ts, Ts ... > ::Handler  ...;

    using Handler < Variant < Ts ... > , Ts, Ts ... > ::operator=...;

//  -------------------------------------------------------------------------------------------

    template < typename T > auto holds_alternative() const
    {
        return this->m_index == Handler < Variant < Ts ... > , T, Ts ... > ::s_index;
    }

//  -------------------------------------------------------------------------------------------

    template < typename T > auto get() const
    {
        return *this->template get_type < T > ();
    }

//  -------------------------------------------------------------------------------------------

    template < typename V > auto visit(V && visitor) const
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
    auto visit_implementation(V && visitor, Deque < U, Us ... > ) const
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

/////////////////////////////////////////////////////////////////////////////////////////////////

class Visitor
{
public :

    void operator()(int x) const
    {
        std::cout << "Visitor::operator() : x = " << x << '\n';
    }

//  ---------------------------------------------------------------------

    void operator()(std::string const & string) const
    {
        std::cout << "Visitor::operator() : string = " << string << '\n';
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////

class Entity
{ 
public : 

    Entity(int) {}

//  -------------------------------------

   ~Entity() 
    { 
		std::cout << "Entity::~Entity\n";
	} 
};

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Variant < int, std::string > variant_1;
    
    Variant < int, std::string > variant_2 = 2;

    Variant < int, std::string > variant_3 = variant_2;

    Variant < int, std::string > variant_4 = std::move(variant_3);

//  --------------------------------------------------------------

    variant_3 = variant_2;

    variant_4 = std::move(variant_3);

    variant_1 = 1;

//  --------------------------------------------------------------

    assert(variant_1.holds_alternative < int > ());

//  --------------------------------------------------------------

    assert(variant_1.get < int > () == 1);

//  --------------------------------------------------------------

    variant_1.visit(Visitor());
}

/////////////////////////////////////////////////////////////////////////////////////////////////