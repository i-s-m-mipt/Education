#include <iostream>
#include <type_traits>

namespace my {

template<typename T>
char test_is_class(int T::*);

template<typename T>
char (&test_is_class(...))[2];

template<typename T>
struct is_class : std::integral_constant<bool, sizeof(test_is_class<T>(nullptr)) == 1> {};

template<typename T>
inline constexpr bool is_class_v = is_class<T>::value;

template<typename T>
struct add_const {
    using type = const T;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct remove_const {
    using type = T;
};

template<typename T>
struct remove_const<const T> {
    using type = T;
};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

template<typename T>
struct remove_reference {
    using type = T;
};

template<typename T>
struct remove_reference<T&> {
    using type = T;
};

template<typename T>
struct remove_reference<T&&> {
    using type = T;
};

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename T>
struct remove_cv {
    using type = T;
};

template<typename T>
struct remove_cv<const T> {
    using type = T;
};

template<typename T>
struct remove_cv<volatile T> {
    using type = T;
};

template<typename T>
struct remove_cv<const volatile T> {
    using type = T;
};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

template<typename T>
struct remove_cvref {
    using type = remove_cv_t<remove_reference_t<T>>;
};

template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

template<typename T>
struct is_array : std::false_type {};

template<typename T>
struct is_array<T[]> : std::true_type {};

template<typename T, std::size_t N>
struct is_array<T[N]> : std::true_type {};

template<typename T>
inline constexpr bool is_array_v = is_array<T>::value;

template<typename T>
struct remove_extent {
    using type = T;
};

template<typename T>
struct remove_extent<T[]> {
    using type = T;
};

template<typename T, std::size_t N>
struct remove_extent<T[N]> {
    using type = T;
};

template<typename T>
using remove_extent_t = typename remove_extent<T>::type;

template<typename T>
struct is_function : std::false_type {};

template<typename Ret, typename... Args>
struct is_function<Ret(Args...)> : std::true_type {};

template<typename Ret, typename... Args>
struct is_function<Ret(Args..., ...)> : std::true_type {};

template<typename T>
inline constexpr bool is_function_v = is_function<T>::value;

template<typename T>
struct add_pointer {
    using type = typename remove_reference<T>::type*;
};

template<typename T>
using add_pointer_t = typename add_pointer<T>::type;

template<typename T>
struct decay {
private:
    using U = remove_cvref_t<T>;
public:
    using type = typename std::conditional<
        is_array_v<U>,
        typename remove_extent<U>::type*,
        typename std::conditional<
            is_function_v<U>,
            add_pointer_t<U>,
            U
        >::type
    >::type;
};

template<typename T>
using decay_t = typename decay<T>::type;

template<bool B, typename T, typename F>
struct conditional {
    using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template<bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

}

enum class E { A };
union U { int a; float b; };

int main() {
    struct Dummy {};
    
    static_assert(!my::is_class_v<int>);
    static_assert(my::is_class_v<std::string>);
    static_assert(my::is_class_v<Dummy>);
    static_assert(!my::is_class_v<E>);
    // static_assert(!my::is_class_v<U>);

    static_assert(std::is_same_v<my::add_const_t<int>, const int>);
    static_assert(std::is_same_v<my::add_const_t<const int>, const int>);
    static_assert(std::is_same_v<my::remove_const_t<const int>, int>);
    static_assert(std::is_same_v<my::remove_const_t<int>, int>);

    static_assert(std::is_same_v<my::decay_t<int[5]>, int*>);
    static_assert(std::is_same_v<my::decay_t<int[]>, int*>);
    static_assert(std::is_same_v<my::decay_t<int(int)>, int(*)(int)>);
    static_assert(std::is_same_v<my::decay_t<const int&>, int>);
    static_assert(std::is_same_v<my::decay_t<volatile int&&>, int>);
    static_assert(std::is_same_v<my::decay_t<const volatile int>, int>);
    static_assert(std::is_same_v<my::decay_t<const int[10]>, int*>);

    static_assert(std::is_same_v<my::conditional_t<true, int, double>, int>);
    static_assert(std::is_same_v<my::conditional_t<false, int, double>, double>);

    static_assert(my::is_class_v<Dummy> == true);
    static_assert(my::is_array_v<int[5]> == true);
    static_assert(my::is_function_v<int(double)> == true);
    
    std::cout << "All tests passed!\n";
    return 0;
}