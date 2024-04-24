#include <bit>
#include <cstddef>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <variant>

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

        constexpr  Storage() noexcept = default;
        constexpr ~Storage() noexcept = default;

    public: // note: only non-const versions for demonstration

        template < typename T > [[nodiscard]] constexpr T * buffer_as() const noexcept
        { 
            return std::bit_cast < T * > (&m_buffer); // note: consider std::launder optimization
        }

        [[nodiscard]] constexpr void * buffer() noexcept { return &m_buffer; }

    public:

        std::size_t current_index = 0; // note: public instead of trivial getters and setters

    private:

        alignas(Ts...) std::byte m_buffer[sizeof(max_type < List < Ts ... > > )];
        
    }; // template < typename ... Ts > class Storage 

} // namespace detail

// =================================================================================================

namespace detail
{
    template < typename D, typename T, typename ... Ts > class Selection // note: non-polymorphic base class
    {
    protected:

        constexpr  Selection() noexcept = default;
        constexpr ~Selection() noexcept = default;

    public:

        constexpr explicit Selection(const T & value) 
        { 
            new (derived().buffer()) T(value); update();
        }

        constexpr explicit Selection(T && value) noexcept 
        { 
            new (derived().buffer()) T(std::move(value)); update();
        }
        
        constexpr D & operator=(const T & value)
        {
            if (derived().current_index == index) 
            {
                *(derived().template buffer_as < T > ()) = value;
            }
            else 
            {
                derived().destroy(); new (derived().buffer()) T(value); update();
            }

            return derived();
        }

        constexpr D & operator=(T && value) noexcept
        {
            if (derived().current_index == index) 
            {
                *(derived().template buffer_as < T > ()) = std::move(value);
            }
            else 
            {
                derived().destroy(); new (derived().buffer()) T(std::move(value)); update();
            }

            return derived();
        }

    protected: // note: used in derived class Variant

        constexpr void destroy() noexcept
        {
            if (derived().current_index == index) derived().template buffer_as < T > ()->~T();
        }

    private: // note: only non-const versions for demonstration

        [[nodiscard]] constexpr D & derived() noexcept { return *(static_cast < D * > (this)); }

        constexpr void update() noexcept { derived().current_index = index; }

    protected:

        static constexpr auto index = index_v < List < Ts ... > , T > + 1;

    }; // template < typename D, typename T, typename ... Ts > class Selection

} // namespace detail

// =================================================================================================

template < typename ... Ts > class Variant : private detail::Storage < Ts ... > , 

    private detail::Selection < Variant < Ts ... > , Ts, Ts ... > ...
{
public:

    using Derived = Variant < Ts ... > ;

    using detail::Selection < Derived, Ts, Ts ... > ::Selection...;
    using detail::Selection < Derived, Ts, Ts ... > ::operator=...;

public:

    constexpr Variant() { *this = detail::front < detail::List < Ts ... > > (); }

    constexpr Variant(const Variant & other) 
    {
        if (!other.empty()) other.visit([this](const auto & value){ *this = value; });
    }

    constexpr Variant(Variant && other) noexcept
    {
        if (!other.empty()) other.visit([this](auto && value){ *this = std::move(value); });
    }

    constexpr Variant & operator=(const Variant & other)
    {
        other.empty() ? destroy() : other.visit([this](const auto & value) { *this = value; });
            
        return *this;
    }

    constexpr Variant & operator=(Variant && other)
    {
        other.empty() ? destroy() : other.visit([this](const auto & value) { *this = std::move(value); });
            
        return *this;
    }

   ~Variant() noexcept { destroy(); }

public:

    [[nodiscard]] constexpr bool empty() const noexcept { return this->current_index == 0; }

    template < typename T > [[nodiscard]] constexpr bool is() const noexcept
    {
        return (this->current_index == detail::Selection < Derived, T, Ts ... > ::index);
    }

    template < typename R, typename V > [[nodiscard]] constexpr R visit(V && visitor)  
    {
        return do_visit < R > (std::forward < V > (visitor), detail::List < Ts ... > ());
    }

    template < typename T > [[nodiscard]] constexpr const T & get() const
    {
        if (empty() || !is < T > ()) throw std::bad_variant_access();

        return *(this->template buffer_as < T > ());
    }  

private:

    template < typename R, typename V, typename U, typename ... Us >

    [[nodiscard]] constexpr R do_visit(V && visitor, detail::List < U, Us ... > )
    {
        if (this->template is < U > ()) 
        {
            return static_cast < R > (visitor(this->template get < U > ()));
        }
        else if constexpr (sizeof...(Us) > 0) 
        {
            return do_visit < R > (std::forward < V > (visitor), detail::List < Us ... > ());
        }
        else throw std::bad_variant_access();
    }

    constexpr void destroy() noexcept
    {
        (detail::Selection < Derived, Ts, Ts ... > ::destroy(), ... ); // note: fold expression

        this->current_index = 0;
    }

private:

    template < typename D, typename U, typename ... Us > friend class detail::Selection;

}; // template < typename ... Ts > class Variant

// =================================================================================================

int main()
{
    Variant < int, double, std::string > field(17);
    if (field.is < int >()) 
    {
        std::cout << "Field stores the integer " << field.get < int > () << std::endl;
    }
    field = 42;
    field = "hello";
    std::cout << "Field now stores the string " << field.get < std::string > () << std::endl;

    // =================================================================================================

    Variant < short, float, char const * > v1(static_cast < short > (123));

    //Variant < int, std::string, double > v2(v1);
    //std::cout << "v2 contains the integer " << v2.get < int > () << '\n';

    v1 = 3.14f;
    //Variant < double, int, std::string > v3(std::move(v1));
    //std::cout << "v3 contains the double " << v3.get < double > () << '\n';

    v1 = "hello";
    //Variant < double, int, std::string > v4(std::move(v1));
    //std::cout << "v4 contains the string " << v4.get < std::string > () << '\n';

    // =================================================================================================

    Variant < int, double > v_1;
    if (v_1.is < int > ())
    {
        std::cout << "Default-constructed v stores the int " << v_1.get < int > () << '\n';
    }
    Variant < double, int > v_2;
    if (v_2.is < double > ())
    {
        std::cout << "Default-constructed v2 stores the double " << v_2.get < double > () << '\n';
    }
}