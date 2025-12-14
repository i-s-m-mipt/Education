#include <cstddef>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > struct Deque {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Size {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > struct Size < Deque < Ts ... > >
{
    constexpr static auto value = sizeof...(Ts);
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > constexpr auto size_v = Size < D > ::value;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > constexpr auto is_empty_v = size_v < D > == 0;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Front {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > struct Front < Deque < T, Ts ... > > 
{ 
    using type = T;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using front = typename Front < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D > struct Push_Front {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > struct Push_Front < T, Deque < Ts ... > >
{
    using type = Deque < T, Ts ... > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D > using push_front = typename Push_Front < T, D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Pop_Front {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > struct Pop_Front < Deque < T, Ts ... > >
{
    using type = Deque < Ts ... > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using pop_front = typename Pop_Front < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Back {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct Back < Deque < T > > 
{ 
    using type = T;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > struct Back < Deque < T, Ts ... > > 
{ 
    using type = typename Back < Deque < Ts ... > > ::type;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using back = typename Back < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D, bool C = is_empty_v < D > > struct Push_Back {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D > struct Push_Back < T, D, false >
{
    using type = push_front < front < D > , typename Push_Back < T, pop_front < D > > ::type > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D > struct Push_Back < T, D, true >
{
    using type = push_front < T, D > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename D > using push_back = typename Push_Back < T, D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Pop_Back {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct Pop_Back < Deque < T > > 
{ 
    using type = Deque <> ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > struct Pop_Back < Deque < T, Ts ... > >
{
    using type = push_front < T, typename Pop_Back < Deque < Ts ... > > ::type > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using pop_back = typename Pop_Back < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, std::size_t I > class Nth : public Nth < pop_front < D > , I - 1 > {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Nth < D, 0 > : public Front < D > {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, std::size_t I > using nth = typename Nth < D, I > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, bool C = is_empty_v < D > > class Max_Type {};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Max_Type < D, false >
{
private :

    using current_t = front < D > ;

    using max_t = typename Max_Type < pop_front < D > > ::type;

public :

    using type = std::conditional_t < sizeof(current_t) >= sizeof(max_t), current_t, max_t > ;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > class Max_Type < D, true > 
{ 
public : 

    using type = std::byte;
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using max_type = typename Max_Type < D > ::type;

////////////////////////////////////////////////////////////////////////////////////////////////
// НОВЫЙ КОД: Проверка наличия типа T в Deque
////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T > struct Has {};

////////////////////////////////////////////////////////////////////////////////////////////////
// Специализация для пустой Deque - тип не найден
////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct Has < Deque < > , T >
{ 
    constexpr static bool value = false; 
};

////////////////////////////////////////////////////////////////////////////////////////////////
// Специализация для непустой Deque - проверяем голову и хвост
////////////////////////////////////////////////////////////////////////////////////////////////

template < typename Head, typename ... Tail, typename T > 
struct Has < Deque < Head, Tail ... > , T >
{
private:
    constexpr static bool found_in_head = std::is_same_v < Head, T >;
    constexpr static bool found_in_tail = Has < Deque < Tail ... > , T > ::value;
    
public:
    constexpr static bool value = found_in_head || found_in_tail;
};

template < typename D, typename T > 
constexpr bool has_v = Has < D, T > ::value;

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(size_v < Deque <     > > == 0 && is_empty_v < Deque <     > > == 1);

    static_assert(size_v < Deque < int > > == 1 && is_empty_v < Deque < int > > == 0);

//  ------------------------------------------------------------------------------------------

    static_assert(std::is_same_v <      front <      Deque < int > > ,         int        > );

    static_assert(std::is_same_v < push_front < int, Deque < int > > , Deque < int, int > > );

    static_assert(std::is_same_v <  pop_front <      Deque < int > > , Deque <          > > );

//  ------------------------------------------------------------------------------------------

    static_assert(std::is_same_v <       back <      Deque < int > > ,              int   > );

    static_assert(std::is_same_v <  push_back < int, Deque < int > > , Deque < int, int > > );

    static_assert(std::is_same_v <   pop_back <      Deque < int > > , Deque <          > > );

//  ------------------------------------------------------------------------------------------

    static_assert(std::is_same_v < nth < Deque < int, int >, 0 > , int > );

    static_assert(std::is_same_v < nth < Deque < int, int >, 1 > , int > );

//  ------------------------------------------------------------------------------------------

    static_assert(std::is_same_v < max_type < Deque < int, double > > , double > );


    using MyDeque = Deque < int, double, char, float, long >;
    
    // Тест 1: Проверка наличия типов в Deque
    static_assert(has_v < MyDeque, int > == true,    "int должен быть в Deque");
    static_assert(has_v < MyDeque, double > == true, "double должен быть в Deque");
    static_assert(has_v < MyDeque, char > == true,   "char должен быть в Deque");
    static_assert(has_v < MyDeque, float > == true,  "float должен быть в Deque");
    static_assert(has_v < MyDeque, long > == true,   "long должен быть в Deque");
    
    // Тест 2: Проверка отсутствия типов
    static_assert(has_v < MyDeque, bool > == false,      "bool не должен быть в Deque");
    static_assert(has_v < MyDeque, short > == false,     "short не должен быть в Deque");
    static_assert(has_v < MyDeque, unsigned > == false,  "unsigned не должен быть в Deque");
    
    // Тест 3: Проверка пустой Deque
    static_assert(has_v < Deque < >, int > == false,    "В пустой Deque ничего нет");
    static_assert(has_v < Deque < >, void > == false,   "В пустой Deque ничего нет");
    
    // Тест 4: Проверка с повторяющимися типами
    using DuplicateDeque = Deque < int, double, int, float >;
    static_assert(has_v < DuplicateDeque, int > == true,    "int должен быть найден");
    static_assert(has_v < DuplicateDeque, double > == true, "double должен быть найден");
    static_assert(has_v < DuplicateDeque, float > == true,  "float должен быть найден");
    
    // Тест 5: Проверка граничных случаев
    using SingleDeque = Deque < int >;
    static_assert(has_v < SingleDeque, int > == true,     "int должен быть в Deque из одного элемента");
    static_assert(has_v < SingleDeque, double > == false, "double не должен быть в Deque из одного элемента");
    
    // Тест 6: Проверка с пользовательскими типами
    struct MyStruct {};
    struct AnotherStruct {};
    using CustomDeque = Deque < MyStruct, AnotherStruct, int >;
    
    static_assert(has_v < CustomDeque, MyStruct > == true,      "MyStruct должен быть в Deque");
    static_assert(has_v < CustomDeque, AnotherStruct > == true, "AnotherStruct должен быть в Deque");
    static_assert(has_v < CustomDeque, double > == false,       "double не должен быть в Deque");
}

////////////////////////////////////////////////////////////////////////////////////////////////