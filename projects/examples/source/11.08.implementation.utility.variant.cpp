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

    template < typename L, bool C = empty_v < L > > struct Max_Type {};

    template < typename L > struct Max_Type < L, true  > { using type = char; };

    template < typename L > struct Max_Type < L, false >
    {
    private:

        using contender = front < L > ;

        using best = typename Max_Type < pop_front < L > > ::type;

    public:

        using type = std::conditional_t < (sizeof(contender) >= sizeof(best)), contender, best > ;
    };

    template < typename L > using max_type = typename Max_Type < L > ::type;

//  ------------------------------------------------------------------------------------------------

    template < typename L, typename T, std::size_t I = 0, bool C = empty_v < L > > struct Index;

    template < typename L, typename T, std::size_t I > struct Index < L, T, I, true  > {};

    template < typename L, typename T, std::size_t I > struct Index < L, T, I, false > 
    :
        std::conditional_t 
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

//      ---------------------------------------------------------

        template < typename T > auto buffer() const
        {
            return std::bit_cast < T * > (&m_buffer);
        }

//      ---------------------------------------------------------------------------

        alignas(Ts...) std::byte m_buffer[sizeof(max_type < List < Ts ... > > )]{}; 

//      ---------------------------------------------------------------------------

        std::size_t current_index = 0; 
    }; 
}

//  ================================================================================================

namespace detail
{
    template < typename D, typename T, typename ... Ts > class Selector
    {
    protected:

        Selector() = default;
       ~Selector() = default;

    public:

        explicit Selector(T value) 
        { 
            std::construct_at(derived().template buffer < T > (), std::move(value)); 
            
            update();
        }

        auto & operator=(T value)
        {
            if (derived().current_index == index) 
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

    private:

        auto & derived()
        {
            return *static_cast < D * > (this); 
        }

        void update() 
        { 
            derived().current_index = index; 
        }

    protected:

        void destroy()
        {
            if (derived().current_index == index) 
            {
                derived().template buffer < T > ()->~T();
            }
        }

//      --------------------------------------------------------------------------------------------

        static constexpr auto index = index_v < List < Ts ... > , T > + 1;
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

//  ----------------------------------------------------------------

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
		using std::swap; 

        swap(this->m_buffer, other.m_buffer);

		swap(this->current_index, other.current_index);
	}

private:

    void destroy()
    {
        (detail::Selector < derived_t, Ts, Ts ... > ::destroy(), ... );

        this->current_index = 0;
    }

public:

    template < typename T > auto holds_alternative() const
    {
        return this->current_index == detail::Selector < derived_t, T, Ts ... > ::index;
    }

    template < typename T > const auto & get() const
    {
        if (!holds_alternative < T > ()) 
        {
            throw std::runtime_error("invalid type");
        }

        return *this->template buffer < T > ();
    }  

    template < typename T > auto & get()
    {
        if (!holds_alternative < T > ()) 
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

    template 
    < 
        typename V, typename U, typename ... Us 
    > 
    void visit_implementation(V && visitor, detail::List < U, Us ... > ) const
    {
        if (this->template holds_alternative < U > ()) 
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

private:

    template < typename D, typename U, typename ... Us > friend class detail::Selector;
};

//  ================================================================================================

struct Entity 
{ 
    explicit Entity(int) {} 
};

//  ================================================================================================

int main()
{
    Variant < int, std::string > variant_1, variant_2(2);

//  --------------------------------------------------------------------------------

    assert(variant_1.holds_alternative < int > () && variant_1.get < int > () == 0);
    assert(variant_2.holds_alternative < int > () && variant_2.get < int > () == 2);

//  --------------------------------------------------------------------------------

    Variant < int, std::string > variant_3(variant_2);

    Variant < int, std::string > variant_4(std::move(variant_3));

    variant_3 = variant_2; 
    
    variant_4 = std::move(variant_3);

    variant_4 = 4;

//  --------------------------------------------------------------------------------

    assert(variant_3.holds_alternative < int > () && variant_3.get < int > () == 2);
    assert(variant_4.holds_alternative < int > () && variant_4.get < int > () == 4);    

//  ---------------------------------------------------------------------------------------

    variant_4.visit([](const auto & data){ std::cout << "variant_4 = " << data << '\n'; });

//  ---------------------------------------------------------------------------------------

//  Variant < Entity, int > variant_5; // error

    Variant < std::monostate, int > variant_6;
}
