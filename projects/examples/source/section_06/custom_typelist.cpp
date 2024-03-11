#include <iostream>

template < typename ... Types > struct List {};

template < typename Type                     > struct Front_Type {};
template < typename Type, typename ... Types > struct Front_Type < List < Type, Types ... > > 
{ 
    using type = Type; 
};

template < typename T > using Front = typename Front_Type < T > ::type;

template < typename Type                     > struct Pop_Front_Type {};
template < typename Type, typename ... Types > struct Pop_Front_Type < List < Type, Types ... > >
{
    using type = List < Types... > ;
};

template < typename T > using Pop_Front = typename Pop_Front_Type < T > ::type;

template < typename List, typename NewElement >
class PushFrontT;

template < typename ... Elements, typename NewElement >
class PushFrontT < Typelist < Elements ... >, NewElement >
{
public:
    using Type = Typelist < NewElement, Elements ... >;
};

template < typename List, typename NewElement >
using PushFront = typename PushFrontT < List, NewElement > ::Type;

template < typename List, std::size_t N >
class NthElementT : public NthElementT < PopFront < List > , N - 1 > {};

template < typename List >
class NthElementT < List, 0 > : public FrontT < List > {};

template < typename List, unsigned N >
using NthElement = typename NthElementT < List, N > ::Type;

template < typename List >
class IsEmpty
{
public:
    static constexpr bool value = false;
};

template < >
class IsEmpty < Typelist < > >
{
public:
    static constexpr bool value = true;
};

template < typename List, typename NewElement, bool = IsEmpty < List > ::value >
class PushBackRecT;

template < typename List, typename NewElement >
class PushBackRecT < List, NewElement, false >
{
private:
    using Head = Front < List >;
    using Tail = PopFront < List > ;
    using NewTail = typename PushBackRecT < Tail, NewElement > ::Type;
public:
    using Type = PushFront < NewTail, Head >;
};

template < typename List, typename NewElement >
class PushBackRecT < List, NewElement, true >
{
public:
    using Type = PushFront < List, NewElement >;
};

template < typename List, typename NewElement >
class PushBackT : public PushBackRecT < List, NewElement > {};

template < typename List, typename NewElement >
using PushBack = typename PushBackT < List, NewElement > ::Type;

template < typename List, template < typename T > class MetaFun,
           bool Empty = IsEmpty < List > ::value >
class TransformT;

/*
* Recursive realization
template < typename List, template < typename T > class MetaFun >
class TransformT < List, MetaFun, false > : 
    public PushFrontT 
        < typename TransformT < PopFront < List >, MetaFun > ::Type,
          typename MetaFun < Front < List >> ::Type > {};

template < typename List, template < typename T > class MetaFun >
class TransformT < List, MetaFun, true >
{
public:
    using Type = List;
};
*
*/

// Pack exspansion realization
template < typename ... Elements, template < typename T > class MetaFun >
class TransformT < Typelist < Elements ... >, MetaFun, false>
{
public:
    using Type = Typelist < typename MetaFun < Elements > ::Type ... >;
};

template < typename List, template < typename T > class MetaFun >
using Transform = typename TransformT < List, MetaFun > ::Type;


template < typename T >
struct AddConstT
{
    using Type = T const;
};

template < typename T >
using AddConst = typename AddConstT < T > ::Type;

template < typename List,
           template < typename X, typename Y > class F,
           typename I,
           bool = IsEmpty < List > ::value >
class AccumulateT;

template < typename List,
           template < typename X, typename Y > class F,
           typename I >
class AccumulateT < List, F, I, false >
    : public AccumulateT < PopFront < List >, F, typename F < I, Front < List > > ::Type > {};

template < typename List,
           template < typename X, typename Y > class F,
           typename I >
class AccumulateT < List, F, I, true >
{
public:
    using Type = I;
};

template < typename List,
           template < typename X, typename Y > class F,
           typename I >
using Accumulate = typename AccumulateT < List, F, I > ::Type;

template < typename List >
using Reverse = Accumulate < List, PushFrontT, Typelist < > >;

int main()
{
    using SignedlntegralTypes = Typelist < signed char, short, int, long, long long >;

    std::cout << typeid(SignedlntegralTypes).name() << std::endl;
    std::cout << typeid(Front < SignedlntegralTypes >).name() << std::endl;
    std::cout << typeid(PopFront < SignedlntegralTypes >).name() << std::endl;
    std::cout << typeid(PushFront < SignedlntegralTypes, int >).name() << std::endl;
    std::cout << typeid(PushBack < SignedlntegralTypes, int >).name() << std::endl;
    std::cout << typeid(Transform < SignedlntegralTypes, AddConstT >).name() << std::endl;
    std::cout << typeid(Reverse < SignedlntegralTypes >).name() << std::endl;

    return EXIT_SUCCESS;
}
