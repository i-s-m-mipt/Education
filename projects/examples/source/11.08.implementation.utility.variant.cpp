#include <bit>
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

#include <gtest/gtest.h>

// =================================================================================================

namespace detail
{
    template < typename ... Ts > struct List {};

    template < typename     L  > struct Size {};

    template < typename ... Ts > struct Size < List < Ts ... > >
    {
        static constexpr auto value = sizeof...(Ts);
    };

    template < typename L > inline constexpr auto  size_v = Size < L > ::value;

    template < typename L > inline constexpr auto empty_v = (size_v < L > == 0);

    // =================================================================================================

    template <             typename     L  > struct Front {};

    template < typename T, typename ... Ts > struct Front < List < T, Ts ... > > { using type = T; };

    template < typename L > using front = typename Front < L > ::type;

    // =================================================================================================

    template <             typename     L  > struct Pop_Front {};

    template < typename T, typename ... Ts > struct Pop_Front < List < T, Ts ... > >
    {
        using type = List < Ts ... > ;
    };

    template < typename L > using pop_front = typename Pop_Front < L > ::type;

    // =================================================================================================

    template < typename L, bool E = empty_v < L > > struct Max_Type {};

    template < typename L > struct Max_Type < L, true  > { using type = char; };

    template < typename L > struct Max_Type < L, false >
    {
    private:

        using contender = front < L > ;

        using best = typename Max_Type < pop_front < L > > ::type;

    public:

        using type = std::conditional_t < (sizeof(contender) >= sizeof(best)), contender, best > ;

    }; // template < typename L > class Max_Type < L, false >

    template < typename L > using max_type = typename Max_Type < L > ::type;

    // =================================================================================================

    template < typename L, typename T, auto N = 0, bool E = empty_v < L > > struct Index;

    template < typename L, typename T, auto N > struct Index < L, T, N, true  > {};

    template < typename L, typename T, auto N > struct Index < L, T, N, false > :

        public std::conditional_t < std::is_same_v < front < L > , T > ,

            std::integral_constant < std::size_t, N > , Index < pop_front < L > , T, N + 1 > > {};

    template < typename L, typename T > inline constexpr auto index_v = Index < L, T > ::value;

} // namespace detail

// =================================================================================================

namespace detail
{
    template < typename ... Ts > class Storage // note: non-polymorphic base class
    {
    protected:

        Storage() noexcept = default;
       ~Storage() noexcept = default;

    protected:

        template < typename T > [[nodiscard]] T * buffer_as() const noexcept // note: need C++26
        {
            return std::bit_cast < T * > (&m_buffer); // note: consider std::launder optimization
        }

    public:

        std::size_t current_index = 0; // note: public instead of trivial getters and setters

    private:

        alignas(Ts...) std::byte m_buffer[sizeof(max_type < List < Ts ... > > )]{};
        
    }; // template < typename ... Ts > class Storage 

} // namespace detail

// =================================================================================================

namespace detail
{
    template < typename D, typename T, typename ... Ts > class Selection // note: non-polymorphic base class
    {
    protected:

        Selection() noexcept = default;
       ~Selection() noexcept = default;

    public: // note: construct_at from C++20 instead of placement new for constexpr support

        explicit Selection(const T & value) 
        { 
            std::construct_at(derived().template buffer_as < T > (), value); update();
        }

        explicit Selection(T && value) noexcept 
        { 
            std::construct_at(derived().template buffer_as < T > (), std::move(value)); update();
        }
        
        D & operator=(const T & value)
        {
            if (derived().current_index == index) 
            {
                *(derived().template buffer_as < T > ()) = value;
            }
            else 
            {
                derived().destroy(); 
                
                std::construct_at(derived().template buffer_as < T > (), value); update();
            }

            return derived();
        }

        D & operator=(T && value) noexcept
        {
            if (derived().current_index == index) 
            {
                *(derived().template buffer_as < T > ()) = std::move(value);
            }
            else 
            {
                derived().destroy(); 
                
                std::construct_at(derived().template buffer_as < T > (), std::move(value)); update();
            }

            return derived();
        }

    private:

        [[nodiscard]] const D & derived() const noexcept { return *(static_cast < const D * > (this)); }
        [[nodiscard]]       D & derived()       noexcept { return *(static_cast <       D * > (this)); }

        void update() noexcept { derived().current_index = index; }

    protected: // note: used in derived class Variant

        void destroy() noexcept
        {
            if (derived().current_index == index) derived().template buffer_as < T > ()->~T();
        }

        static constexpr auto index = index_v < List < Ts ... > , T > + 1;

    }; // template < typename D, typename T, typename ... Ts > class Selection

} // namespace detail

// =================================================================================================

template < typename ... Ts > class Variant : 

    private detail::Storage < Ts ... > , 

    private detail::Selection < Variant < Ts ... > , Ts, Ts ... > ... // note: variadic base classes
{
public:

    template < typename ... Us > using List = detail::List < Us ... > ;

    using Derived = Variant < Ts ... > ;

    using detail::Selection < Derived, Ts, Ts ... > ::Selection...;
    using detail::Selection < Derived, Ts, Ts ... > ::operator=...; // note: inherited operator= from Selection

public:

    Variant() { *this = detail::front < List < Ts ... > > (); }

    Variant(const Variant & other) 
    {
        if (!other.empty()) other.visit([this](const auto & value){ *this = value; });
    }

    Variant(Variant && other) noexcept
    {
        if (!other.empty()) other.visit([this](auto && value){ *this = std::move(value); });
    }

    Variant & operator=(const Variant & other)
    {
        other.empty() ? destroy() : other.visit([this](const auto & value) { *this = value; });
            
        return *this;
    }

    Variant & operator=(Variant && other)
    {
        other.empty() ? destroy() : other.visit([this](const auto & value) { *this = std::move(value); });
            
        return *this;
    }

    ~Variant() noexcept { destroy(); }

public:

    [[nodiscard]] bool empty() const noexcept { return this->current_index == 0; }

    template < typename V > void visit(V && visitor) const
    {
        do_visit(std::forward < V > (visitor), List < Ts ... > ());
    }

    template < typename T > [[nodiscard]] bool has() const noexcept
    {
        return (this->current_index == detail::Selection < Derived, T, Ts ... > ::index);
    }

    template < typename T > [[nodiscard]] const T & get() const
    {
        if (empty() || !has < T > ()) throw std::bad_variant_access();

        return *(this->template buffer_as < T > ());
    }  

private:

    template < typename V, typename U, typename ... Us > void do_visit(V && visitor, List < U, Us ... > ) const
    {
        if (this->template has < U > ()) 
        {
            visitor(this->template get < U > ());
        }
        else if constexpr (sizeof...(Us) > 0) 
        {
            do_visit(std::forward < V > (visitor), List < Us ... > ());
        }
        else throw std::bad_variant_access();
    }

    void destroy() noexcept
    {
        (detail::Selection < Derived, Ts, Ts ... > ::destroy(), ... ); // note: fold expression

        this->current_index = 0;
    }

private:

    template < typename D, typename U, typename ... Us > friend class detail::Selection;

}; // template < typename ... Ts > class Variant : ...

// =================================================================================================

class C { public: constexpr explicit C(int) {} }; // note: not default constructible

// =================================================================================================

TEST(Variant, Functions)
{
    Variant < char, int, double > variant_1;

    variant_1 = 'a'; ASSERT_TRUE(variant_1.has < char   > () && variant_1.get < char   > () == 'a');
    variant_1 = 100; ASSERT_TRUE(variant_1.has < int    > () && variant_1.get < int    > () == 100);
    variant_1 = 1.0; ASSERT_TRUE(variant_1.has < double > () && variant_1.get < double > () == 1.0);

    Variant < char, int, double > variant_2(42);

    variant_1 = variant_2;

    ASSERT_TRUE(variant_1.has < int > () && variant_1.get < int > () == 42);

//  Variant < C, int > variant_3; // error: not default constructible

    Variant < std::monostate, int > variant_4;
}

// =================================================================================================

int main(int argc, char ** argv) // note: arguments for testing
{
    Variant < char, int, double > variant(3.14);

    try
    {
        std::ignore = variant.get < int > ();
    }
    catch(const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }

    variant = 42;

    variant.visit([](auto x){ std::cout << x << std::endl; });

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}