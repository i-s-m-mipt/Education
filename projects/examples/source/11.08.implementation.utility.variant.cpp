#pragma once
#include <iostream>
#include <new>
#include <utility>
#include <cassert>
#include <exception>
#include <type_traits>

#include "Typelist.hpp"

// =================================================================================================

template < typename Tlist, typename T, unsigned N = 0, bool E = empty_v < Tlist > > struct IndOfT;

template < typename Tlist, typename T, unsigned N > struct IndOfT < Tlist, T, N, false >:
    public std::conditional_t < std::is_same < front < Tlist >, T > ::value,
                                std::integral_constant < unsigned, N >,
                                IndOfT < pop_front < Tlist >, T, N + 1 > > { };

template < typename Tlist, typename T, unsigned N > struct IndOfT < Tlist, T, N, true > { };

// =================================================================================================

template < typename ... Ts > class VariantStorage 
{
public:
    unsigned char getDiscriminator() const { return discriminator; }
    void setDiscriminator(unsigned char d) { discriminator = d; }

    void* getRawBuffer() { return buffer; }
    const void* getRawBuffer() const { return buffer; }

    template < typename T > T* getBufferAs()
    { 
        return std::launder(reinterpret_cast < T* > (buffer)); // change way of cast?
    }
    template < typename T > T const* getBufferAs() const
    {
        return std::launder(reinterpret_cast < T const* > (buffer)); // change way of cast?
    }

private:
    using maxT = max_type < Tlist < Ts ... > >;
    alignas(Ts ... ) unsigned char buffer[sizeof(maxT)];
    unsigned char discriminator = 0;
};

// =================================================================================================

template < typename ... Ts > class Variant;

template < typename T, typename ... Ts > class VariantChoice
{
private:
    using Derived = Variant < Ts ... >;

public:
    VariantChoice() { }
    VariantChoice(T const& value);
    VariantChoice(T&& value);
    bool destroy();
    Derived& operator= (T const& value);
    Derived& operator= (T&& value);

protected:
    constexpr static unsigned Discriminator = IndOfT < Tlist < Ts ... >, T > ::value + 1;

private:
    Derived& getDerived()
    {
        return *static_cast < Derived* > (this); // is static_cast ok?
    }
    Derived const& getDerived() const
    {
        return *static_cast < Derived const * > (this); // is static_cast ok?
    }
};

// =================================================================================================

template < typename T, typename ... Ts > bool VariantChoice < T, Ts ... > ::destroy()
{
    if (getDerived().getDiscriminator() == Discriminator)
    {
        getDerived().template getBufferAs < T > () -> ~T(); // template???
        return true;
    }
    return false;
}

// =================================================================================================

template < typename T, typename ... Ts > auto VariantChoice < T, Ts ... > ::operator= (T const& value) -> Derived&
{
    if (getDerived().getDiscriminator() == Discriminator)
        *getDerived().template getBufferAs < T > () = value;
    else 
    {
        getDerived().destroy();
        new(getDerived().getRawBuffer()) T(value);
        getDerived().setDiscriminator(Discriminator);
    }
    return getDerived();
}

template < typename T, typename ... Ts > auto VariantChoice < T, Ts ... > ::operator= (T&& value) -> Derived&
{
    if (getDerived().getDiscriminator() == Discriminator)
        *getDerived().template getBufferAs < T > () = std::move(value);
    else 
    {
        getDerived().destroy();
        new(getDerived().getRawBuffer()) T(std::move(value));
        getDerived().setDiscriminator(Discriminator);
    }
    return getDerived();
}

// =================================================================================================

template < typename T, typename ... Ts > VariantChoice < T, Ts ... > ::VariantChoice(T const& value)
{
    new(getDerived().getRawBuffer()) T(value);
    getDerived().setDiscriminator(Discriminator);
}

template < typename T, typename ... Ts > VariantChoice < T, Ts ... > ::VariantChoice(T&& value)
{
    new(getDerived().getRawBuffer()) T(std::move(value));
    getDerived().setDiscriminator(Discriminator);
}

// =================================================================================================

class CompResT;

template < typename Vis, typename T > using VisElemRes = decltype(std::declval < Vis > () (std::declval < T > ()));

template < typename R, typename Vis, typename ... Ts > class VisResT { public: using type = R; };

template < typename Vis, typename ... Ts > class VisResT < CompResT, Vis, Ts ... >
{
public:
    using type = std::common_type_t < VisElemRes < Vis, Ts > ... >;
};

template < typename R, typename Vis, typename ... Ts > using VisRes = typename VisResT < R, Vis, Ts ... > ::type;

// =================================================================================================

template < typename ... Ts >
class Variant : private VariantStorage < Ts ... >, private VariantChoice < Ts, Ts ... > ...
{
public:
    template < typename T > bool is() const;
    template < typename T > T& get()&;
    template < typename T > T const& get() const&;
    template < typename T > T&& get()&&;         

    template < typename R = CompResT, typename Vis > VisRes < R, Vis, Ts& ... > visit(Vis&& vis)&;
    template < typename R = CompResT, typename Vis > VisRes < R, Vis, Ts const&... > visit(Vis&& vis) const&;
    template < typename R = CompResT, typename Vis > VisRes< R, Vis, Ts&& ... > visit(Vis&& vis)&&;

    using VariantChoice < Ts, Ts ... > ::VariantChoice ...;
    Variant();
    Variant(Variant const& source);
    Variant(Variant&& source);
    template < typename ... SourceTs > Variant(Variant < SourceTs ... > const& source);
    template < typename ... SourceTs > Variant(Variant < SourceTs ... > && source);

    using VariantChoice < Ts, Ts ... > ::operator= ...;
    Variant& operator= (Variant const& source);
    Variant& operator= (Variant&& source);
    template < typename ... SourceTs > Variant& operator= (Variant < SourceTs ... > const& source);
    template < typename ... SourceTs > Variant& operator= (Variant < SourceTs ... > && source);

    bool empty() const { return this -> getDiscriminator() == 0; }

    ~Variant() { destroy(); }
    void destroy();

private:
    template < typename T, typename ... OtherTs > friend class VariantChoice;
};

// =================================================================================================

template < typename ... Ts > template < typename T > bool Variant < Ts ... > ::is() const
{
    return this->getDiscriminator() == VariantChoice < T, Ts ... > ::Discriminator;
}

// =================================================================================================

class EmptyVariant : public std::exception { };
    
template < typename ... Ts > template < typename T > T& Variant < Ts ... > ::get()&
{
    if (empty()) { throw EmptyVariant(); }
    assert(is < T > ()); // may be process in another way?
    return *this -> template getBufferAs < T > (); // how does this work? template?
}

template < typename ... Ts > template < typename T > const T& Variant < Ts ... > ::get() const &
{
    if (empty()) { throw EmptyVariant(); }
    assert(is < T > ()); // may be process in another way?
    return *this -> template getBufferAs < T > ();
}

template < typename ... Ts > template < typename T > T&& Variant < Ts ... > ::get()&&
{
    if (empty()) { throw EmptyVariant(); }
    assert(is < T >()); // may be process in another way?
    return std::forward < T > (*this -> template getBufferAs < T > ()); // how does this work? template?
}

// =================================================================================================

template < typename ... Ts > void Variant < Ts ... > ::destroy()
{
    (VariantChoice < Ts, Ts ... > ::destroy(), ... ); // convolution expression
    this->setDiscriminator(0);
}

// =================================================================================================

template < typename R, typename V, typename Vis, typename T, typename ... Ts >
R variantVisitImpl(V&& variant, Vis&& vis, Tlist < T, Ts ... >)
{
    if (variant.template is < T > ()) {
        return static_cast < R > (std::forward < Vis > (vis) 
            (std::forward < V > (variant).template get < T > ()));
    }
    else if constexpr (sizeof ... (Ts) > 0) 
    {
        return variantVisitImpl < R > (std::forward < V > (variant), 
            std::forward < Vis > (vis), Tlist < Ts ... > ());
    }
    else
    {
        throw EmptyVariant();
    }
}

template < typename ... Ts > template < typename R, typename Vis >
VisRes < R, Vis, Ts& ... > Variant < Ts ... > ::visit(Vis&& vis)&
{
    using Res = VisRes < R, Vis, Ts& ... >;
    return variantVisitImpl < Res > (*this, std::forward < Vis > (vis), Tlist < Ts ... > ());
}

template < typename ... Ts > template < typename R, typename Vis >
VisRes < R, Vis, Ts const & ... > Variant < Ts ... > ::visit(Vis&& vis) const&
{
    using Res = VisRes < R, Vis, Ts const& ... >;
    return variantVisitImpl < Res > (*this, std::forward < Vis > (vis), Tlist < Ts ... > ());
}

template < typename ... Ts > template < typename R, typename Vis >
VisRes < R, Vis, Ts&& ... > Variant < Ts ... > ::visit(Vis&& vis)&&
{
    using Result = VisRes < R, Vis, Ts&& ... >;
    return variantVisitImpl < Result > (std::move(*this), std::forward < Vis > (vis), Tlist < Ts ... > ());
}

// =================================================================================================

template < typename ... Ts >  Variant < Ts ... > ::Variant() { *this = front < Tlist < Ts ... > > (); }

template < typename ... Ts > Variant < Ts ... > ::Variant(Variant const& source) 
{
    if (!source.empty())
        source.visit([ & ](auto const& value) { *this = value; });
}

template < typename ... Ts > Variant < Ts ... > ::Variant(Variant&& source)
{
    if (!source.empty())
        source.visit([&](auto&& value) { *this = std::move(value); });
}

template < typename ... Ts > template < typename ... SourceTs >
Variant < Ts ... > ::Variant(Variant < SourceTs ... > const& source)
{
    if (!source.empty())
        source.visit([ & ](auto const& value) { *this = value; });
}

template < typename ... Ts > template < typename ... SourceTs >
Variant < Ts ... > ::Variant(Variant < SourceTs ... > && source)
{
    if (!source.empty())
        source.visit([ & ](auto&& value) { *this = std::move(value); });
}

// =================================================================================================

template < typename ... Ts > Variant < Ts ... > & Variant < Ts ... > ::operator= (Variant const& source)
{
    if (!source.empty())
        source.visit([ & ](auto const& value) { *this = value; });
    else
        destroy();
    return *this;
}

template < typename ... Ts > Variant < Ts ... > & Variant < Ts ... > ::operator= (Variant&& source)
{
    if (!source.empty())
        source.visit([ & ](auto&& value) { *this = std::move(value); });
    else
        destroy();
    return *this;
}

template < typename ... Ts > template < typename ... SourceTs >
Variant < Ts ... > & Variant < Ts ... > ::operator= (Variant < SourceTs ... > const& source) // template cctor: why sould we distinguish it?
{
    if (!source.empty())
        source.visit([ & ](auto const& value) { *this = value; });
    else
        destroy();
    return *this;
}

template < typename ... Ts > template < typename ... SourceTs >
Variant < Ts ... > & Variant < Ts ... > ::operator= (Variant < SourceTs ... > && source)
{
    if (!source.empty())
        source.visit([ & ](auto&& value) { *this = std::move(value); });
    else
        destroy();
    return *this;
}

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

    Variant < int, std::string, double > v2(v1);
    std::cout << "v2 contains the integer " << v2.get < int > () << '\n';

    v1 = 3.14f;
    Variant < double, int, std::string > v3(std::move(v1));
    std::cout << "v3 contains the double " << v3.get < double > () << '\n';

    v1 = "hello";
    Variant < double, int, std::string > v4(std::move(v1));
    std::cout << "v4 contains the string " << v4.get < std::string > () << '\n';

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