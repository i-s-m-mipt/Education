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

using namespace std::literals;

//  ================================================================================================

namespace detail
{
    template < typename ... Ts > struct List {};

//  ------------------------------------------------------------------------------------------------

    template < typename     T  > struct Size {};

    template < typename ... Ts > struct Size < List < Ts ... > >
    {
        static constexpr auto value = sizeof...(Ts);
    };

    template < typename L > constexpr auto size_v = Size < L > ::value;

    template < typename L > constexpr auto empty_v = size_v < L > == 0;

//  ------------------------------------------------------------------------------------------------

    template <             typename     T  > struct Front {};

    template < typename T, typename ... Ts > struct Front < List < T, Ts ... > > 
    { 
        using type = T; 
    };

    template < typename L > using front = typename Front < L > ::type;

//  ------------------------------------------------------------------------------------------------

    template <             typename     T  > struct Pop_Front {};

    template < typename T, typename ... Ts > struct Pop_Front < List < T, Ts ... > >
    {
        using type = List < Ts ... > ;
    };

    template < typename L > using pop_front = typename Pop_Front < L > ::type;

//  ------------------------------------------------------------------------------------------------

    template < typename L, bool C = empty_v < L > > class Max_Type {};

    template < typename L > class Max_Type < L, true  > { public: using type = char; };

    template < typename L > class Max_Type < L, false >
    {
    private:

        using contender = front < L > ;

        using best = typename Max_Type < pop_front < L > > ::type;

    public:

        using type = std::conditional_t < (sizeof(contender) >= sizeof(best)), contender, best > ;
    };

    template < typename L > using max_type = typename Max_Type < L > ::type;

//  ------------------------------------------------------------------------------------------------

    template < typename L, typename T, std::size_t I = 0, bool C = empty_v < L > > class Index;

    template < typename L, typename T, std::size_t I > class Index < L, T, I, true  > {};

    template < typename L, typename T, std::size_t I > class Index < L, T, I, false > 
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

//  ------------------------------------------------------------------------------------------------

namespace detail
{
    template < typename ... Ts > class Recorder
    {
    protected:

        Recorder() = default;
       ~Recorder() = default;

    //  ---------------------------------------------------------------------------

        template < typename T > auto buffer() const
        {
            return std::bit_cast < T * > (&m_buffer);
        }

    //  ---------------------------------------------------------------------------

        alignas(Ts...) std::byte m_buffer[sizeof(max_type < List < Ts ... > > )]{}; 

        std::size_t index = 0; 
    }; 
}

//  ================================================================================================

namespace detail
{
    template < typename D, typename T, typename ... Ts > class Selector
    {
    public:

        explicit Selector(T value) 
        { 
            std::construct_at(derived().template buffer < T > (), std::move(value)); 
            
            update();
        }

        auto & operator=(T value)
        {
            if (derived().index == s_index) 
            {
                *derived().template buffer < T > () = std::move(value);
            }
            else 
            {
                derived().destroy(); 
                
                std::construct_at(derived().template buffer < T > (), std::move(value));
                
                update();
            }

            return derived();
        }

    protected:

        Selector() = default;
       ~Selector() = default;

    //  --------------------------------------------------------------------------------

        void destroy()
        {
            if (derived().index == s_index) 
            {
                derived().template buffer < T > ()->~T();
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
            derived().index = s_index; 
        }
    };
}

//  ================================================================================================

template < typename ... Ts > class Variant 
: 
    private detail::Recorder           < Ts ... > , 
    private detail::Selector < Variant < Ts ... > , Ts, Ts ... > ...
{
public:

    using derived_t = Variant < Ts ... > ;

//  -------------------------------------------------------------------------------------------

    using detail::Selector < derived_t, Ts, Ts ... > ::Selector ...;
    using detail::Selector < derived_t, Ts, Ts ... > ::operator=...;

//  -------------------------------------------------------------------------------------------

    Variant() 
    { 
        *this = detail::front < detail::List < Ts ... > > (); 
    }

    Variant(const Variant & other) : detail::Selector < derived_t, Ts, Ts ... > ::Selector()...
    {
        other.visit([this](auto && value){ *this = value; });
    }

    Variant(Variant && other)
    {
        other.visit([this](auto && value){ *this = std::move(value); });
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

//  -------------------------------------------------------------------------------------------

    void swap(Variant & other)
	{
        std::swap(this->m_buffer, other.m_buffer);

		std::swap(this->index, other.index);
	}

//  -------------------------------------------------------------------------------------------

    template < typename T > auto has() const
    {
        return this->index == detail::Selector < derived_t, T, Ts ... > ::s_index;
    }

    template < typename T > auto get() const
    {
        if (!has < T > ()) 
        {
            throw std::runtime_error("invalid type");
        }

        return *this->template buffer < T > ();
    }  

    template < typename V > void visit(V && visitor) const
    {
        visit_implementation(std::forward < V > (visitor), detail::List < Ts ... > ());
    }

private:

    template < typename D, typename U, typename ... Us > friend class detail::Selector;

//  -------------------------------------------------------------------------------------------

    void destroy()
    {
        (detail::Selector < derived_t, Ts, Ts ... > ::destroy(), ... ); this->index = 0;
    }

//  -------------------------------------------------------------------------------------------

    template 
    < 
        typename V, typename U, typename ... Us 
    > 
    void visit_implementation(V && visitor, detail::List < U, Us ... > ) const
    {
        if (this->template has < U > ()) 
        {
            visitor(this->template get < U > ());
        }
        else if constexpr (sizeof...(Us) > 0) 
        {
            visit_implementation(std::forward < V > (visitor), detail::List < Us ... > ());
        }
        else 
        {
            throw std::runtime_error("invalid type");
        }
    }
};

//  ================================================================================================

class Entity 
{ 
public:

    explicit Entity(int) {} 
};

//  ================================================================================================

int main()
{
    Variant < int, std::string > variant_1;
    
    Variant < int, std::string > variant_2(2);

//  --------------------------------------------------

    Variant < int, std::string > variant_3(variant_2);

    Variant < int, std::string > variant_4(std::move(variant_3));

    variant_3 = variant_2; 
    
    variant_4 = std::move(variant_3);

    variant_4 = 4;

//  ------------------------------------------------------------------

    assert(variant_4.has < int > () && variant_4.get < int > () == 4);    

//  -------------------------------------------------------------------------------

    variant_4.visit([](auto data){ std::cout << "variant_4 = " << data << '\n'; });

//  -------------------------------------------------------------------------------

//  Variant < Entity, int > variant_5; // error

    Variant < std::monostate, Entity, int > variant_6;
}
