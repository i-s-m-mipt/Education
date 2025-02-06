#include <bit>
#include <cassert>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

//////////////////////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    template < typename ... Ts > struct List {};

//  ----------------------------------------------------------------------------------------------

    template < typename L > struct Size {};

    template < typename ... Ts > struct Size < List < Ts ... > >
    {
        static constexpr auto value = sizeof...(Ts);
    };

    template < typename L > constexpr auto size_v = Size < L > ::value;

    template < typename L > constexpr auto empty_v = size_v < L > == 0;

//  ----------------------------------------------------------------------------------------------

    template < typename L > struct Front {};

    template < typename T, typename ... Ts > struct Front < List < T, Ts ... > > 
    { 
        using type = T;
    };

    template < typename L > using front = typename Front < L > ::type;

//  ----------------------------------------------------------------------------------------------

    template < typename L > struct Pop_Front {};

    template < typename T, typename ... Ts > struct Pop_Front < List < T, Ts ... > >
    {
        using type = List < Ts ... > ;
    };

    template < typename L > using pop_front = typename Pop_Front < L > ::type;

//  ----------------------------------------------------------------------------------------------

    template < typename L, bool C = empty_v < L > > class Max_Type {};

    template < typename L > class Max_Type < L, 1 > { public: using type = char; };

    template < typename L > class Max_Type < L, 0 >
    {
    private:

        using contender = front < L > ;

        using best = typename Max_Type < pop_front < L > > ::type;

    public:

        using type = std::conditional_t < (sizeof(contender) >= sizeof(best)), contender, best > ;
    };

    template < typename L > using max_type = typename Max_Type < L > ::type;

//  ----------------------------------------------------------------------------------------------

    template < typename L, typename T, std::size_t I = 0, bool C = empty_v < L > > class Index {};

    template < typename L, typename T, std::size_t I > class Index < L, T, I, 1 > {};

    template < typename L, typename T, std::size_t I > class Index < L, T, I, 0 > 
    :
        public std::conditional_t 
        < 
            std::is_same_v < front < L > , T > ,

            std::integral_constant < std::size_t, I > , 

            Index < pop_front < L > , T, I + 1 > 
        > 
    {};

    template < typename L, typename T > constexpr auto index_v = Index < L, T > ::value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    template < typename ... Ts > class Storage
    {
    protected:

        Storage() = default;

       ~Storage() = default;

    //  ---------------------------------------------------------------------------

        template < typename T > auto array() const
        {
            return std::bit_cast < T * > (&m_data);
        }

    //  ---------------------------------------------------------------------------

        alignas(Ts...) std::byte m_data[sizeof(max_type < List < Ts ... > > )]{};

        std::size_t m_index = 0;
    };
}

//////////////////////////////////////////////////////////////////////////////////////////////////

namespace detail
{
    template < typename D, typename T, typename ... Ts > class Handler
    {
    public:

        Handler(T x) 
        { 
            std::construct_at(derived().template array < T > (), std::move(x));
            
            update();
        }

        auto & operator=(T x)
        {
            if (derived().m_index == s_index) 
            {
                *derived().template array < T > () = std::move(x);
            }
            else 
            {
                derived().destroy();
                
                std::construct_at(derived().template array < T > (), std::move(x));
                
                update();
            }

            return derived();
        }

    protected:

        Handler() = default;

       ~Handler() = default;

    //  --------------------------------------------------------------------------------

        void destroy()
        {
            if (derived().m_index == s_index) 
            {
                derived().template array < T > ()->~T();
            }
        }

    //  --------------------------------------------------------------------------------

        static constexpr auto s_index = index_v < List < Ts ... > , T > + 1;

    private:

        auto & derived()
        {
            return *static_cast < D * > (this);
        }

        void update() 
        { 
            derived().m_index = s_index;
        }
    };
}

//////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > class Variant 
: 
    private detail::Storage           < Ts ... > , 

    private detail::Handler < Variant < Ts ... > , Ts, Ts ... > ...
{
public:

    using derived_t = Variant < Ts ... > ;

//  ----------------------------------------------------------------------------------------------

    using detail::Handler < derived_t, Ts, Ts ... > ::Handler...;

    using detail::Handler < derived_t, Ts, Ts ... > ::operator=...;

//  ----------------------------------------------------------------------------------------------

    Variant() 
    { 
        *this = detail::front < detail::List < Ts ... > > ();
    }

    Variant(const Variant & other) : detail::Handler < derived_t, Ts, Ts ... > ::Handler()...
    {
        other.visit([this](auto && x){ *this = x; });
    }

    Variant(Variant && other)
    {
        other.visit([this](auto && x){ *this = std::move(x); });
    }

    auto & operator=(Variant other)
    {
        swap(other);

		return *this;
    }

   ~Variant() 
    { 
        destroy();
    }

//  ----------------------------------------------------------------------------------------------

    void swap(Variant & other)
	{
        std::swap(this->m_data , other.m_data );

		std::swap(this->m_index, other.m_index);
	}

//  ----------------------------------------------------------------------------------------------

    template < typename T > auto has() const
    {
        return this->m_index == detail::Handler < derived_t, T, Ts ... > ::s_index;
    }

    template < typename T > auto get() const
    {
        if (!has < T > ()) 
        {
            throw std::runtime_error("invalid type");
        }

        return *this->template array < T > ();
    }  

    template < typename V > auto visit(V && visitor) const
    {
        return visit_implementation(std::forward < V > (visitor), detail::List < Ts ... > ());
    }

private:

    template < typename D, typename U, typename ... Us > friend class detail::Handler;

//  ----------------------------------------------------------------------------------------------

    void destroy()
    {
        (detail::Handler < derived_t, Ts, Ts ... > ::destroy(), ... );
        
        this->m_index = 0;
    }

//  ----------------------------------------------------------------------------------------------

    template 
    < 
        typename V, typename U, typename ... Us 
    > 
    auto visit_implementation(V && visitor, detail::List < U, Us ... > ) const
    {
        if (this->template has < U > ()) 
        {
            return visitor(this->template get < U > ());
        }
        else if constexpr (sizeof...(Us) > 0) 
        {
            return visit_implementation(std::forward < V > (visitor), detail::List < Us ... > ());
        }
        else 
        {
            throw std::runtime_error("invalid type");
        }
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////

class Visitor
{
public:

    void operator()(int x) const
    {
        std::cout << "Visitor::operator() : x = " << x << '\n';
    }

    void operator()(const std::string & string) const
    {
        std::cout << "Visitor::operator() : string = " << string << '\n';
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////

class Entity 
{ 
public:

    Entity(int) {} 
};

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        Variant < int, std::string > variant_1;
    
        Variant < int, std::string > variant_2 = 2;

        Variant < int, std::string > variant_3(variant_2);

        Variant < int, std::string > variant_4(std::move(variant_3));

        variant_3 = variant_2;
        
        variant_4 = std::move(variant_3);

        variant_4 = 4;
    }

//  ------------------------------------------------------------------

    {
        Variant < int, std::string > variant = 1;

        assert(variant.has < int > () && variant.get < int > () == 1);

        variant.visit(Visitor());
    }

//  ------------------------------------------------------------------

    {
//      Variant < Entity, int > variant; // error

        Variant < std::monostate, Entity, int > variant;
    }
}
